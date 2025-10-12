// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTriggerBox.h"

// Sets default values for this component's properties
AMyTriggerBox::AMyTriggerBox()
{

}

// Called when the game starts
void AMyTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapEnd);
}

void AMyTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor && OtherActor == this)
	{
		return;
	}

	bool AcceptableActor = GetAcceptableActor();

	if (AcceptableActor)
	{
		Mover->SetShouldMove(true);
	}
}

void AMyTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor && OtherActor == this)
	{
		return;
	}

	bool AcceptableActor = GetAcceptableActor();

	if (!AcceptableActor)
	{
		Mover->SetShouldMove(false);
	}
}

bool AMyTriggerBox::GetAcceptableActor()
{
	TArray<AActor*>	Actors;
	GetOverlappingActors(Actors);

	for (AActor *Actor : Actors) 
	{
		if (Actor->ActorHasTag(AcceptableActorTag))
		{
			return true;
		}
	}

	return false;
}

void AMyTriggerBox::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}