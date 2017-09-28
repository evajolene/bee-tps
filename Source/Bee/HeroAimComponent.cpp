// Copyright 2017 Eva Jolene.

#include "HeroAimComponent.h"
#include "HeroPawn.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonCameraActor.h"

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
		//Let aim component tick after pawn has moved.
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
			heroPawn->fireTarget = location + direction * 100.0f;
		}
	}
}