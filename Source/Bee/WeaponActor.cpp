// Copyright 2017 Eva Jolene.

#include "WeaponActor.h"
#include "WeaponComponent.h"
#include "Engine/StaticMesh.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;

	meshComponent = FindComponentByClass<UStaticMeshComponent>();
	if (meshComponent == nullptr)
	{
		meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
		RootComponent = meshComponent;
		meshComponent->RegisterComponent();
	}
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	if (weaponComponentToAdd)
	{
		weaponComponent = NewObject<UWeaponComponent>(this, weaponComponentToAdd->GetDefaultObject()->GetClass());
		weaponComponent->RegisterComponent();
		meshComponent->SetStaticMesh(weaponComponent->mesh);
	}
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

