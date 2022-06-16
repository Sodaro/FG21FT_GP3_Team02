// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SGLogbookEntry.generated.h"

/**
 * 
 */
UCLASS()
class TEAM02GP3_API ULogbookEntry : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FText Content;
};
