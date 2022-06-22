// Fill out your copyright notice in the Description page of Project Settings.


#include "SGLorePickup.h"
#include "Components/StaticMeshComponent.h"
// Called when the game starts or when spawned
void ASGLorePickup::BeginPlay()
{
	Super::BeginPlay();

	if (DataHandle.IsNull())
		return;

	FString ContextString = "";
	auto DataPtr = DataHandle.GetRow<FSGLogStruct>(ContextString);

	if (DataPtr == nullptr)
	{
		return;
	}
	RowData = *DataPtr;
}

