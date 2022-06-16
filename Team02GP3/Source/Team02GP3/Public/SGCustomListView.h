// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "SGCustomListView.generated.h"

/**
 * 
 */
UCLASS()
class TEAM02GP3_API USGCustomListView : public UListView
{
	GENERATED_BODY()

	USGCustomListView(const FObjectInitializer& Initializer);

protected:
	virtual TSharedRef<STableViewBase> RebuildListWidget() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Bar Style"))
		FScrollBarStyle WidgetBarStyle;
};
