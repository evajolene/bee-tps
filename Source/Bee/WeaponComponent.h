// Copyright 2017 Eva Jolene.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ABulletActor> bulletActorToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float fireDelay = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float bulletSpeed = 80.0f;

	float fireTime = 0.0f;

public:
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Fire(FVector StartingLocation, FVector Direction);
	void Reload();
};
