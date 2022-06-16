// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SGBlueprintFunctionLibrary.generated.h"

class APlayerController;
UCLASS()
class TEAM02GP3_API USGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, Category = "SG|Input")
    static void SetMouseSensitivity(float Value, APlayerController* Controller);

    UFUNCTION(BlueprintCallable, Category = "SG|Input")
    static float GetMouseSensitivity(APlayerController* Controller);

    UFUNCTION(BlueprintCallable, Category = "SG|Input")
    static float GetMouseSensitivityX(APlayerController* Controller);

    UFUNCTION(BlueprintCallable, Category = "SG|Input")
    static float GetMouseSensitivityY(APlayerController* Controller);

    UFUNCTION(BlueprintCallable, Category = "SG|Input")
    static void ApplyInputSettings(APlayerController* Controller);
};
