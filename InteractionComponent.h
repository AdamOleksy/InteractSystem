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

	//List of close interactable components
	TArray<UInteractable*> InteractableComponentsList;

	//To sort list with interactable components by priority
	void SortList();

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Function to add interactable  to priority list
	void AddInteractableToList(UInteractable* NewInteractableComponent);

	//Function to remove interactable from priority list
	void RemoveInteractableFromList(UInteractable* ComponentToRemove);
	
	//To interact with highest priority interactable component if it is available
	void InteractWithComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
