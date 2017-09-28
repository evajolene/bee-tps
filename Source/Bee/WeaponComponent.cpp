// Copyright 2017 Eva Jolene.

#include "WeaponComponent.h"
#include "Engine/World.h"
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
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	fireTime -= DeltaTime;
}

void UWeaponComponent::Fire(FVector StartingLocation, FVector Direction)
{
	if (bulletActorToSpawn == nullptr || fireTime > 0.0f)
	{
		return;
	}
	FTransform bulletTransform = FTransform(FQuat::Identity, StartingLocation, FVector::OneVector);
	ABulletActor* bulletActor = GetWorld()->SpawnActor<ABulletActor>(bulletActorToSpawn->GetDefaultObject()->GetClass(), bulletTransform);
	bulletActor->velocity = Direction * bulletSpeed;
	fireTime = fireDelay;
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