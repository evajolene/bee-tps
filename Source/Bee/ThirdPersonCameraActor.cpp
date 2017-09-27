// Copyright 2017 Eva Jolene.

#include "ThirdPersonCameraActor.h"
#include "HeroPawn.h"

AThirdPersonCameraActor::AThirdPersonCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AThirdPersonCameraActor::BeginPlay()
{
	Super::BeginPlay();
	SetTickGroup(ETickingGroup::TG_PostPhysics);
}

void AThirdPersonCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (heroPawn)
	{
		FQuat facingDirection = FQuat::MakeFromEuler(FVector(0.0f, heroPawn->pitch, heroPawn->yaw));

		FVector cameraPosition = heroPawn->GetActorLocation();
		cameraPosition.Z += offset.Z;
		cameraPosition += facingDirection.GetForwardVector() * offset.X + facingDirection.GetRightVector() * offset.Y;
		SetActorLocation(cameraPosition);
		SetActorRotation(facingDirection);

		heroPawn->interactOffset = FVector(35.0f, offset.Y, offset.Z);
	}
}

