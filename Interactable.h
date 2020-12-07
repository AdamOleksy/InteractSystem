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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractComponents", meta = (AllowPrivateAccess = "true"))
	float SphereSize = 300.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractComponents", meta = (AllowPrivateAccess = "true"))
	int32 InteractPriority = 0;

	// declare overlap begin function, adding component to player list
 	UFUNCTION()
 	void OnBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function, removing component from player list
	UFUNCTION()
 	void OnOverlapEnd( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);
	
	//To check if actor is not blocked by other objects
	bool IsActorVisible(AActor* OtherActor);

	//To check if player is looking at interactable
	bool IsActorLookingAt(AActor* OtherActor);

	//To sort list by proity every time it is updatad
	void SortList();

	

public:	
	// Sets default values for this component's properties
	UInteractable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:	

	bool CanInteract(AActor* OtherActor);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 GetPriorityNumber() const;

	void Interact();
		
};
