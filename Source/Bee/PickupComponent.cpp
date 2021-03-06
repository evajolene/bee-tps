// Copyright 2017 Eva Jolene.

#include "PickupComponent.h"
#include "DrawDebugHelpers.h"
#include "HeroPawn.h"
#include "WeaponActor.h"
#include "WeaponComponent.h"
#include "HeroAimComponent.h"
#include "EngineUtils.h"

UPickupComponent::UPickupComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Requires use with specific actor.
	AHeroPawn* heroPawn = Cast<AHeroPawn>(GetOwner());
	if (heroPawn == nullptr)
	{
		return;
	}

	if (heroPawn->bWasInteractInputPressed)
	{
		FQuat facingDirection = FQuat::MakeFromEuler(FVector(0.0f, heroPawn->pitch, heroPawn->yaw));
		FVector interactLocation = heroPawn->GetActorLocation();
		interactLocation.Z += heroPawn->interactOffset.Z;
		interactLocation += facingDirection.GetForwardVector() * heroPawn->interactOffset.X + facingDirection.GetRightVector() * heroPawn->interactOffset.Y;

		AWeaponActor* weaponActor = GetWeaponActorToPickUp(interactLocation, 35.0f);
		PickUpWeapon(heroPawn, weaponActor);

		heroPawn->bWasInteractInputPressed = 0;
	}
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

void UPickupComponent::PickUpWeapon(AHeroPawn* Owner, AWeaponActor* WeaponActor)
{
	bool bIsPickUpValid = (WeaponActor != nullptr && WeaponActor->weaponComponent != nullptr);
	
	if (bIsPickUpValid)
	{
		UClass* weaponToPickUpClass = WeaponActor->weaponComponent->GetClass();

		//Get rid of our weapon if it's a different weapon to pick up.
		if (Owner->weaponComponent && weaponToPickUpClass != Owner->weaponComponent->GetClass())
		{
			Owner->weaponComponent->CloneAsWeaponPickup(Owner->GetActorLocation());
			Owner->weaponComponent->DestroyComponent();
			Owner->weaponComponent = nullptr;
		}

		//Pick up a new weapon if we just got rid of one, or just don't have one.
		if (Owner->weaponComponent == nullptr)
		{
			Owner->weaponComponent = NewObject<UWeaponComponent>(GetOwner(), weaponToPickUpClass);
			Owner->weaponComponent->RegisterComponent();

			UHeroAimComponent* aimComponent = Owner->FindComponentByClass<UHeroAimComponent>();
			if (aimComponent)
			{
				Owner->weaponComponent->AddTickPrerequisiteComponent(aimComponent);
			}
		}

		Owner->weaponComponent->ammo += WeaponActor->ammo;

		WeaponActor->Destroy();
	}
}