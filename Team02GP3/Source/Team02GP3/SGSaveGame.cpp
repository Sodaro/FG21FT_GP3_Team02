#include "SGSaveGame.h"
#include "TEAM02GP3.h"
#include "Player Character/SGPlayerCharacter.h"
#include "Player Character/SGPlayerCharacterLanternComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SGInteractableActor.h"

void USGSaveGame::InitializeInteractables()
{
	for (auto& Elem : SaveInteractables)
	{
		if (Elem.Key != nullptr)
		{
			Elem.Key->OnGameLoad(Elem.Value);
		}
	}
}

USGSaveGame::USGSaveGame()
{
	PlayerTransform = FTransform();
	LogbookKeys = TArray<FName>();
}

void ASGPlayerCharacter::SaveGame()
{
	//Create an instance of the SaveGame class
	USGSaveGame* SaveGameInstance = Cast<USGSaveGame>(UGameplayStatics::CreateSaveGameObject(USGSaveGame::StaticClass()));

	//Saves the players current location
	SaveGameInstance->PlayerTransform = this->GetActorTransform();

	//Saves the Battery %
	SaveGameInstance->CurrentBattery = PlayerLantern->CurrentBattery;

	//Save level
	SaveGameInstance->GetCurrentLevelName = FName(GetWorld()->GetName());
	SaveGameInstance->SavedLevel = GetWorld()->GetCurrentLevel();

	//deep copy the logbook keys so they can be used to initialize the logbook on start
	TArray<FName> LogKeys = GetLogbookKeys();
	for (FName Key : LogKeys)
	{
		SaveGameInstance->LogbookKeys.Emplace(Key);
	}

	//save the interactable objects and whether they have been interacted with or not
	SaveGameInstance->SaveInteractables = Interactables;
	
	//player only has to see intro once / save
	SaveGameInstance->HasWatchedIntro = true;

	//Saves the GameInstance
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SaveSlot"), 0);
}

void ASGPlayerCharacter::LoadGame()
{
	//Create an instance of the SaveGame class
	//USGSaveGame* SaveGameInstance = Cast<USGSaveGame>(UGameplayStatics::CreateSaveGameObject(USGSaveGame::StaticClass()));

	//Loads the saved game instance
	USGSaveGame* SaveGameInstance = Cast<USGSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot", 0));
	if (SaveGameInstance == nullptr)
		return;

	//load level
	UGameplayStatics::OpenLevel(this, SaveGameInstance->GetCurrentLevelName, true);
}

void ASGPlayerCharacter::SaveInteractable(ASGInteractableActor* Interactable)
{
	if (Interactables.Contains(Interactable) == false)
	{
		Interactables.Emplace(Interactable, false);
	}
	Interactables[Interactable] = true;
}
