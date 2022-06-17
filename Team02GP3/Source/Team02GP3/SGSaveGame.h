#pragma once

#include "GameFramework/SaveGame.h"
#include "SGSaveGame.generated.h"

UCLASS()
class TEAM02GP3_API USGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = SaveGame)
	FTransform PlayerTransform;

	UPROPERTY(EditAnywhere, Category = SaveGame)
	int CurrentBattery; 

	UPROPERTY(BlueprintReadOnly)
	FName GetCurrentLevelName;

	UPROPERTY()
	TSoftObjectPtr<UWorld> SavedLevel;

	UPROPERTY()
	TArray<FName> LogbookKeys;

	USGSaveGame();
	


};