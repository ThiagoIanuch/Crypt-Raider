// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Mover.h"
#include "MyTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	AMyTriggerBox();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

public:
	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);

private:
	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;
	
	UMover* Mover;

	bool GetAcceptableActor();
};
