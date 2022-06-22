// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SGEntryListItem.generated.h"

class UTextBlock;
class UButton;
class USGLogBook;
class USGListItem;
class USGEntryListItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEntryDelegate, USGEntryListItem*, Object);

//This is the widget added to the listview which displays category name and shows entry info when clicked
UCLASS()
class TEAM02GP3_API USGEntryListItem : public UUserWidget
{
	GENERATED_BODY()

public:
	//virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NameLabel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ButtonWidget;

	//UPROPERTY()
	//USGListItem* ItemData;

	UFUNCTION()
	void OnClick();

	UPROPERTY()
	USGLogBook* Logbook;

	//UPROPERTY()
	//FText DisplayName;

	UPROPERTY()
	FText Content;

	UPROPERTY()
	FText Title;

	UPROPERTY()
	FText Notes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LogEntry)
	TSoftObjectPtr<UTexture2D> LogImage;

	UPROPERTY(BlueprintAssignable)
	FEntryDelegate OnEntryClicked;

	//UFUNCTION(BlueprintCallable)
	//void AssignLogbook(USGLogBook* InLogbook);

	//UFUNCTION(BlueprintCallable)
	//void DisplayItemData();
};
