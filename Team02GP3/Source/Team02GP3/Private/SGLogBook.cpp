// Fill out your copyright notice in the Description page of Project Settings.


#include "SGLogBook.h"
#include "../Public/SGListItem.h"
#include "Engine/DataTable.h"
#include "SGLogStruct.h"
#include "SGCustomListView.h"
#include "Components/Scrollbox.h"
#include "../Widgets/SGLogCategoryWidget.h"
#include "../Widgets/SGEntryListItem.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USGLogBook::NativeConstruct()
{
	Super::NativeConstruct();
	ListItems.SetNum(0);
	//InventoryListView->SetListItems(ListItems);
	LogImageWidget->SetVisibility(ESlateVisibility::Hidden);
}

void USGLogBook::AddEntries(const TArray<FName>& Keys)
{
	if (DataTable == nullptr || Keys.Num() == 0)
		return;

	for(FName Key : Keys)
	{
		AddEntry(Key, false);
	}
}

TArray<FName>& USGLogBook::GetUsedKeys()
{
	return UsedKeys;
}

bool USGLogBook::AddEntry(FName Key, bool ShouldBroadcastEvent)
{
	
	if (DataTable == nullptr && UsedKeys.Contains(Key) == false)
		return false;

	auto Data = DataTable->FindRow<FSGLogStruct>(Key, "", true);
	if (Data == nullptr)
		return false;



	//Create new item containing the info that will be showed in the log
	//auto Item = NewObject<USGListItem>(this, USGListItem::StaticClass());
	//Item->DisplayName = Data->LogName;
	//Item->Content = Data->LogText;
	USGLogCategoryWidget* LogCategoryWidget = nullptr;
	if (LogCategories.Contains(Data->LogCategory) == false)
	{
		LogCategoryWidget = CreateWidget<USGLogCategoryWidget>(GetWorld(), LogCategoryClass);
		LogCategoryWidget->CategoryText->Text = FText::FromName(Data->LogCategory);
		LogCategories.Emplace(Data->LogCategory, LogCategoryWidget);
		LogScrollBox->AddChild(LogCategoryWidget);
	}
	LogCategoryWidget = LogCategories[Data->LogCategory];
	if (LogCategoryWidget == nullptr)
		return false;

	USGEntryListItem* LogEntryWidget = CreateWidget<USGEntryListItem>(GetWorld(), LogEntryClass);

	LogEntryWidget->NameLabel->SetText(Data->LogName);
	LogEntryWidget->Content = Data->LogContent;
	LogEntryWidget->Title = Data->LogTitle;
	LogEntryWidget->Notes = Data->LogNotes;
	

	//Try to load the assigned image from the datatable
	//image not loaded onstart fix: https://forums.unrealengine.com/t/why-do-i-have-to-click-copy-reference-everytime-one-of-my-blueprints-has-a-compile-error/304477/9
	if (Data->LogImage.IsPending())
	{
		UObject* Asset = Data->LogImage.ToSoftObjectPath().TryLoad();
		if (Asset == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Still couldn't load texture"));
		}
	}

	UTexture2D* Texture = Data->LogImage.Get();
	if (Texture)
	{
		LogEntryWidget->LogImage = Texture;
	}
	LogCategoryWidget->CategoryScrollBox->AddChild(LogEntryWidget);
	LogEntryWidget->OnEntryClicked.AddDynamic(this, &USGLogBook::DisplayContent);

	UsedKeys.Add(Key);
	if (ShouldBroadcastEvent)
	{
		LogbookUpdated.Broadcast(this);
	}
	return true;
}

void USGLogBook::DisplayContent(USGEntryListItem* Item)
{
	USGEntryListItem* Entry = Cast<USGEntryListItem>(Item);
	LogContentTextBlock->SetText(Entry->Content);
	LogTitleTextBlock->SetText(Entry->Title);
	LogNotesTextBlock->SetText(Entry->Notes);
	LogImageWidget->SetBrushFromTexture(Entry->LogImage.Get(), true);
	LogImageWidget->SetVisibility(ESlateVisibility::Visible);
}
