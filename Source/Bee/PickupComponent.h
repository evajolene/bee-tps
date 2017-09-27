// Copyright 2017 Eva Jolene.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEE_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPickupComponent();

protected:
	virtual void BeginPlay() override;

public:	
	//Returns nullptr if there's none in area to pick up.
	class AWeaponActor* GetWeaponActorToPickUp(FVector PickupLocation, float PickupRadius);
};
