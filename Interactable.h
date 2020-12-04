// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Interactable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPPINTERACT_API UInteractable : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractComponents", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* TriggerInteractionSphere = nullptr;

	// declare overlap begin function
	
 	UFUNCTION()
 	void OnBeginOverlap
	(
		 UPrimitiveComponent* OverlappedComp, 
		 AActor* OtherActor, 
		 UPrimitiveComponent* OtherComp, 
		 int32 OtherBodyIndex, 
		 bool bFromSweep, 
		 const FHitResult& SweepResult
	);

	TArray<AActor*> OverlapingActorsList;

	void TryToAddActorToList(AActor*);

	bool CanInteract();

public:	
	// Sets default values for this component's properties
	UInteractable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
