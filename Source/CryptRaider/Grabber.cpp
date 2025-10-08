// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator Rotation = GetComponentRotation();
	//UE_LOG(LogTemp, Display, TEXT("Rotation: %s"), *Rotation.ToCompactString());
	
	UWorld* World = GetWorld();
	double Time = World->TimeSeconds;
	//UE_LOG(LogTemp, Display, TEXT("%lf"), Time);

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(World, Start, End, FColor::Red);

	FHitResult HitResult;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	bool HasHit = World->SweepSingleByChannel(HitResult, 
		Start, End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
	);

	// Print the hit actor name
	if (HasHit) {
		AActor* HitActor = HitResult.GetActor();
		FString HitActorName = HitActor->GetActorNameOrLabel();

		UE_LOG(LogTemp, Display, TEXT("Hit: %s"), *HitActorName);
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Hit: False"));
	}

}

