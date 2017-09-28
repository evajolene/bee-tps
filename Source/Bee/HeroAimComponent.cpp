// Copyright 2017 Eva Jolene.

#include "HeroAimComponent.h"
#include "HeroPawn.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonCameraActor.h"
#include "Trace.h"

UHeroAimComponent::UHeroAimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeroAimComponent::BeginPlay()
{
	Super::BeginPlay();

	heroPawn = Cast<AHeroPawn>(GetOwner());
	if (heroPawn && heroPawn->cameraActor)
	{
		//Let aim component tick after camera has moved.
		AddTickPrerequisiteActor(heroPawn->cameraActor);
	}
}

void UHeroAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (heroPawn == nullptr)
	{
		return;
	}

	APlayerController* playerController = Cast<APlayerController>(heroPawn->GetController());
	if (playerController)
	{
		FVector location, direction;
		if (playerController->DeprojectMousePositionToWorld(location, direction))
		{
			FHitResult hitResult;
			FVector fireAtLocation = location + direction * 1000.0f;
			if (UTrace::SweepWorld(heroPawn, heroPawn->GetActorLocation(), fireAtLocation, hitResult, 2.5f))
			{
				fireAtLocation = hitResult.ImpactPoint;
			}
			heroPawn->fireTarget = fireAtLocation;
		}
	}
}