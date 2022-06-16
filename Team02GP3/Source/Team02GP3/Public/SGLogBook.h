// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "SGLogBook.generated.h"

class UTextBlock;
class UImage;
class UListView;
class USGListItem;
class UDataTable;
class USGCustomListView;
class UScrollBox;
class USGLogCategoryWidget;
class USGEntryListItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLogbookUpdatedSignature, USGLogBook*, Logbook);

UCLASS()
class TEAM02GP3_API USGLogBook : public UUserWidget
{
	GENERATED_BODY()

	int32 CurrentItemIndex = 0;
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* LogScrollBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LogContentTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LogTitleTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LogNotesTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* LogImageWidget;

	TArray<USGListItem*> ListItems;

	TMap<FName, USGLogCategoryWidget*> LogCategories;
	TSet<FName> UsedKeys;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* DataTable;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USGLogCategoryWidget> LogCategoryClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USGEntryListItem> LogEntryClass;
	/**
	* Attempt to add a category to logbook.
	* @param Key used to find entry in datatable.
	* @return True if logbook was successful in adding category, false otherwise.
	*/
	UFUNCTION(BlueprintCallable)
	bool AddEntry(FName Key);

	UFUNCTION(BlueprintCallable)
	void DisplayContent(USGEntryListItem* Item);

	UPROPERTY(BlueprintAssignable)
	FLogbookUpdatedSignature LogbookUpdated;
};
