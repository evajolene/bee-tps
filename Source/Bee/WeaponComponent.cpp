// Copyright 2017 Eva Jolene.

#include "WeaponComponent.h"
#include "Engine/World.h"
#include "HeroPawn.h"
#include "WeaponActor.h"
#include "BulletActor.h"
#include "Engine/StaticMesh.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ammo = 0;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//This component can be held by various classes, but needs our custom pawn class to tick.
	heroPawn = Cast<AHeroPawn>(GetOwner());
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (heroPawn == nullptr)
	{
		return;
	}

	fireTime -= DeltaTime;
}

void UWeaponComponent::Fire(FVector StartingLocation, FVector Direction)
{
	if (bulletActorToSpawn == nullptr || fireTime > 0.0f || ammo == 0)
	{
		return;
	}

	FTransform bulletTransform = FTransform(FQuat::Identity, StartingLocation, FVector::OneVector);
	ABulletActor* bulletActor = GetWorld()->SpawnActor<ABulletActor>(bulletActorToSpawn->GetDefaultObject()->GetClass(), bulletTransform);
	bulletActor->velocity = Direction * bulletSpeed;
	fireTime = fireDelay;
	ammo--;
}

void UWeaponComponent::Reload()
{

}

AWeaponActor* UWeaponComponent::CloneAsWeaponPickup(FVector Location)
{
	FTransform transform = FTransform(FQuat::Identity, Location, FVector::OneVector);
	AWeaponActor* weaponActor = GetWorld()->SpawnActor<AWeaponActor>(AWeaponActor::StaticClass(), transform);
	weaponActor->weaponComponent = NewObject<UWeaponComponent>(weaponActor, GetClass());
	weaponActor->weaponComponent->RegisterComponent();
	weaponActor->meshComponent->SetStaticMesh(mesh);
	weaponActor->ammo = ammo;
	return weaponActor;
}