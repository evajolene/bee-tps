// Copyright 2017 Eva Jolene.

#include "PickupComponent.h"
#include "DrawDebugHelpers.h"
#include "WeaponActor.h"
#include "EngineUtils.h"

UPickupComponent::UPickupComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();
}

AWeaponActor* UPickupComponent::GetWeaponActorToPickUp(FVector PickupLocation, float PickupRadius)
{
	AWeaponActor* nearestActor = nullptr;
	if (GetOwner() && GetWorld())
	{
		DrawDebugSphere
		(
			GetWorld(),
			PickupLocation,
			PickupRadius,
			16,
			FColor(0, 155, 255),
			false,
			1.0f
		);

		float smallestDistance = PickupRadius;
		for (TActorIterator<AWeaponActor> actorIterator(GetWorld()); actorIterator; ++actorIterator)
		{
			AWeaponActor* weaponActor = (*actorIterator);
			FVector toWeaponActor = weaponActor->GetActorLocation() - PickupLocation;
			float distance = toWeaponActor.Size();
			if (distance <= smallestDistance)
			{
				nearestActor = weaponActor;
				smallestDistance = distance;
			}
		}
	}
	return nearestActor;
}

