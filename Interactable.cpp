// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UInteractable::UInteractable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// create trigger capsule
	TriggerInteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Interaction Sphere"));

}


// Called when the game starts
void UInteractable::BeginPlay()
{
	Super::BeginPlay();
	TriggerInteractionSphere->SetSphereRadius(300.f);
	TriggerInteractionSphere->SetCollisionProfileName(TEXT("Trigger"));
	TriggerInteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &UInteractable::OnBeginOverlap);

	
	// ...
	
}


// Called every frame
void UInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInteractable::OnBeginOverlap
	(
		 UPrimitiveComponent* OverlappedComp, 
		 AActor* OtherActor, 
		 UPrimitiveComponent* OtherComp, 
		 int32 OtherBodyIndex, 
		 bool bFromSweep, 
		 const FHitResult& SweepResult
	)
	{
		TryToAddActorToList(OtherActor);
		UE_LOG(LogTemp, Error, TEXT("%i"), OverlapingActorsList.Num()) ;
	}


void UInteractable::TryToAddActorToList(AActor* OverlapingActor)
{
	OverlapingActorsList.Add(OverlapingActor);
}