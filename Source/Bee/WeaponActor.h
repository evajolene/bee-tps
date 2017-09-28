// Copyright 2017 Eva Jolene.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class BEE_API AWeaponActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Component")
		TSubclassOf<class UWeaponComponent> weaponComponentToAdd;

public:
	UStaticMeshComponent* meshComponent;
	UWeaponComponent* weaponComponent;

	UPROPERTY(EditDefaultsOnly)
		uint16 ammo;

	AWeaponActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
