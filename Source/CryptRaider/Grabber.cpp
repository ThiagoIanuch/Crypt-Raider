// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle != nullptr)
	{
		FString PhysicsHandleName = PhysicsHandle->GetName();
		UE_LOG(LogTemp, Display, TEXT("Physics Handle: %s"), *PhysicsHandleName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle found"));
	}

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
	UWorld* World = GetWorld();
	double Time = World->TimeSeconds;

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(World, Start, End, FColor::Red);
	DrawDebugSphere(World, End, 10, 10, FColor::Blue, false, 5);

	FHitResult HitResult;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	bool HasHit = World->SweepSingleByChannel(HitResult, 
		Start, End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
	);

	// Print the hit actor name
	if (HasHit) 
	{
		DrawDebugSphere(World, HitResult.Location, 10, 10, FColor::Green, false, 5);
		DrawDebugSphere(World, HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);

		AActor* HitActor = HitResult.GetActor();
		FString HitActorName = HitActor->GetActorNameOrLabel();

		UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *HitActorName);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit actor: ") + HitActorName);
	}
	else 
	{
		UE_LOG(LogTemp, Display, TEXT("No actor hit"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No actor hit"));
	}
}

void UGrabber::Release() 
{
	UE_LOG(LogTemp, Display, TEXT("Released grabber"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Released grabber"));
}