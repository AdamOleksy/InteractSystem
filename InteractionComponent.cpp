// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "InteractionComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::AddInteractableToList(UInteractable* NewInteractableComponent)
{
	InteractableComponentsList.AddUnique(NewInteractableComponent);
	SortList();
}

void UInteractionComponent::RemoveInteractableFromList(UInteractable* ComponentToRemove)
{
	InteractableComponentsList.Remove(ComponentToRemove);
	SortList();
}

void UInteractionComponent::SortList()
{
	InteractableComponentsList.Sort([](const UInteractable& A, const UInteractable& B) {
        return
            A.GetPriorityNumber() >
            B.GetPriorityNumber();
    });
	InteractWithComponent();

}

void UInteractionComponent::InteractWithComponent()
{
	if (InteractableComponentsList.Num() > 0)
	{
		for(auto inter : InteractableComponentsList)
		{
			if(inter->CanInteract(GetOwner()))
			{
				inter->Interact();
				return;
			}
		}
	}
}


// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Is actor can interact?: %s"), 
// 								CanInteract(OtherActor) ? TEXT("True") : TEXT("False")));
	// //Debug
	// for(auto inter : InteractableComponentsList)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Is actor can interact?: %i"), 
 	// 							inter->GetPriorityNumber() ));
	// }