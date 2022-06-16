// Fill out your copyright notice in the Description page of Project Settings.


#include "SGBlueprintFunctionLibrary.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/InputSettings.h"

void USGBlueprintFunctionLibrary::SetMouseSensitivity(float Value, APlayerController* Controller)
{
	//UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	//FName MouseX = FName(*FString("MouseX"));
	//FName MouseY = FName(*FString("MouseY"));
	//FKey MouseXKey = FKey(MouseX);
	//FInputAxisKeyMapping MouseXMapping(MouseX, MouseXKey);

	FInputAxisProperties MouseAxisProps;
	//Controller->GetGameInstance()->
	//if (Controller->PlayerInput->GetAxisProperties(EKeys::MouseX, MouseAxisProps))
	//{
	//	MouseAxisProps.Sensitivity = Value;
	//	Controller->PlayerInput->SetAxisProperties(EKeys::MouseX, MouseAxisProps);
	//}
	//if (Controller->PlayerInput->GetAxisProperties(EKeys::MouseY, MouseAxisProps))
	//{
	//	MouseAxisProps.Sensitivity = Value;
	//	Controller->PlayerInput->SetAxisProperties(EKeys::MouseY, MouseAxisProps);
	//}
	Controller->PlayerInput->SetMouseSensitivity(Value);
}

float USGBlueprintFunctionLibrary::GetMouseSensitivity(APlayerController* Controller)
{
	return Controller->PlayerInput->GetMouseSensitivity();
}

float USGBlueprintFunctionLibrary::GetMouseSensitivityX(APlayerController* Controller)
{
	return Controller->PlayerInput->GetMouseSensitivityX();
}

float USGBlueprintFunctionLibrary::GetMouseSensitivityY(APlayerController* Controller)
{
	return Controller->PlayerInput->GetMouseSensitivityY();
}

void USGBlueprintFunctionLibrary::ApplyInputSettings(APlayerController* Controller)
{
	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	Settings->SaveConfig();
}
