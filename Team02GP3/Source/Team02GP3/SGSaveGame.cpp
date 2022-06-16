#include "SGSaveGame.h"
#include "TEAM02GP3.h"
#include "Player Character/SGPlayerCharacter.h"
#include "Player Character/SGPlayerCharacterLanternComponent.h"
#include "Kismet/GameplayStatics.h"

USGSaveGame::USGSaveGame()
{
	PlayerTransform = FTransform();
}



void ASGPlayerCharacter::SaveGame()
{
	//Create an instance of the SaveGame class
	USGSaveGame* SaveGameInstance = Cast<USGSaveGame>(UGameplayStatics::CreateSaveGameObject(USGSaveGame::StaticClass()));

	//Saves the players current location
	SaveGameInstance->PlayerTransform = this->GetActorTransform();

	//Saves the Battery %
	SaveGameInstance->CurrentBattery = PlayerLantern->CurrentBattery;

	//SAve level
	SaveGameInstance->GetCurrentLevelName = FName(GetWorld()->GetName());
	SaveGameInstance->SavedLevel = GetWorld()->GetCurrentLevel();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Emerald, SaveGameInstance->GetCurrentLevelName.ToString());


	//Saves the GameInstance
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SaveSlot"), 0);

	//Log message
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Game Saved"));
}

void ASGPlayerCharacter::LoadGame()
{
	//Create an instance of the SaveGame class
	USGSaveGame* SaveGameInstance = Cast<USGSaveGame>(UGameplayStatics::CreateSaveGameObject(USGSaveGame::StaticClass()));

	//Loads the saved game instance
	SaveGameInstance = Cast<USGSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot", 0));
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Emerald, SaveGameInstance->GetCurrentLevelName.ToString());
	//load level
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Emerald, GetWorld()->GetName());
	UGameplayStatics::OpenLevel(this, SaveGameInstance->GetCurrentLevelName, true);
	
	//Loads the set players transform from the save file
	//this->SetActorTransform(SaveGameInstance->PlayerTransform);
	//
	//PlayerLantern->CurrentBattery = SaveGameInstance->CurrentBattery;
	

	//Log message
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Emerald, TEXT("Game Loaded"));
}
