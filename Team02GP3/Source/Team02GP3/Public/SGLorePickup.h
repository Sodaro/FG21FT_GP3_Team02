// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGInteractableActor.h"
#include "SGLogStruct.h"
#include "SGLorePickup.generated.h"

class UDataTable;
class USGLogBook;

UCLASS()
class TEAM02GP3_API ASGLorePickup : public ASGInteractableActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Logbook")
	FDataTableRowHandle DataHandle;

	UPROPERTY(BlueprintReadWrite, Category = "Logbook")
	USGLogBook* LogBook;

	UPROPERTY(BlueprintReadOnly, Category = "Logbook")
	FSGLogStruct RowData;
};
