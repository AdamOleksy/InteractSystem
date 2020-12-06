// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPPINTERACT_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

	TArray<UInteractable*> InteractableComponentsList;

	void SortList();

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddInteractableToList(UInteractable* NewInteractableComponent);

	void RemoveInteractableFromList(UInteractable* ComponentToRemove);

	void InteractWithComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
