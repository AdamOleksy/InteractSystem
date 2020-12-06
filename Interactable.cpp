// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawDebugHelpers.h"
#include "Interactable.h"
#include "InteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
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
	TriggerInteractionSphere->SetSphereRadius(SphereSize);
	TriggerInteractionSphere->SetCollisionProfileName(TEXT("Trigger"));
	TriggerInteractionSphere->SetHiddenInGame(false);
	TriggerInteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &UInteractable::OnBeginOverlap);
	TriggerInteractionSphere->OnComponentEndOverlap.AddDynamic(this, &UInteractable::OnOverlapEnd);
	
	// ...
	
}


// Called every frame
void UInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInteractable::OnBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UInteractionComponent* interactable = OtherActor->FindComponentByClass<UInteractionComponent>();
	if (interactable)
	{
		interactable->AddInteractableToList(this);
	}
	
}


void UInteractable::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UInteractionComponent* interactable = OtherActor->FindComponentByClass<UInteractionComponent>();
	if (interactable)
	{
		interactable->RemoveInteractableFromList(this);
	}
}

bool UInteractable::IsActorVisible(AActor* OtherActor)
{
	
	FVector LineBegin = GetOwner()->GetActorLocation();
	FRotator LookAtPlayerDirectiron = UKismetMathLibrary::FindLookAtRotation(LineBegin, OtherActor->GetActorLocation());
	FVector LineEnd = LineBegin + LookAtPlayerDirectiron.Vector() * (SphereSize+100.f);

	FHitResult Hit;

	bool isHit = GetWorld()->LineTraceSingleByChannel(Hit, LineBegin, LineEnd, ECC_Visibility);

	if(isHit && Hit.GetActor()->FindComponentByClass<UInteractionComponent>())
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool UInteractable::IsActorLookingAt(AActor* OtherActor)
{
	FVector DirectionWherePlayerLookig = OtherActor->GetActorForwardVector();
	FVector LookAtPlayerDirectiron = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), OtherActor->GetActorLocation()).Vector();

	float Dot = FVector::DotProduct(DirectionWherePlayerLookig, LookAtPlayerDirectiron);

	float AngleBetweenVectors = FMath::RadiansToDegrees(FMath::Acos(Dot));

	if(AngleBetweenVectors > 135)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool UInteractable::CanInteract(AActor* OtherActor)
{
	return IsActorVisible(OtherActor) && IsActorLookingAt(OtherActor);
}

int32 UInteractable::GetPriorityNumber() const
{
	return InteractPriority;
}

		// //Debug
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Is actor can interact?: %s"), 
		// 									CanInteract(OtherActor) ? TEXT("True") : TEXT("False")));

void UInteractable::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Is actor can interact?: %s"), 
										*GetOwner()->GetName()));
}