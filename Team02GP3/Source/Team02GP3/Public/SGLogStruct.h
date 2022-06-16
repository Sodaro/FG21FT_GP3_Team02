// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SGLogStruct.generated.h"

USTRUCT(BlueprintType)
struct TEAM02GP3_API FSGLogStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    FSGLogStruct()
        : LogName(),
        InteractionText(),
        LogContent(),
        LogNotes(),
        LogTitle()
    {}

    /**Category for filtering*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LogEntry)
    FName LogCategory;

    /** Name for the entry showed on in the left column */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LogEntry)
    FText LogName;

    /** Text that can be shown when unlocking the log entry */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LogEntry)
    FText InteractionText;

    /** Text shown in the right column of the log, the actual content */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LogEntry)
    FText LogContent;

    /** Text shown below image */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LogEntry)
    FText LogNotes;

    /** Text shown above, journal page title */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LogEntry)
    FText LogTitle;

    /** The image shown above the log content */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LogEntry)
    TAssetPtr<UTexture2D> LogImage;
};
