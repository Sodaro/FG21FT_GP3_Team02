
#pragma once
#include "Engine/DataAsset.h"
#include "SGListItem.generated.h"

UCLASS()
class USGListItem : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FText DisplayName;

	UPROPERTY()
	FText Content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LogEntry)
	TSoftObjectPtr<UTexture2D> LogImage;
};