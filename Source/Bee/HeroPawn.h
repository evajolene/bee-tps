// Copyright 2017 Eva Jolene.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HeroPawn.generated.h"

UCLASS()
class BEE_API AHeroPawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AThirdPersonCameraActor> cameraActorToSpawn;

public:
	class AThirdPersonCameraActor* cameraActor;
	class UWeaponComponent* weaponComponent;
	class UPickupComponent* pickupComponent;

	AHeroPawn();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FVector2D movementInput;
	float yaw, pitch;
	FVector interactOffset;
	uint8 bWasInteractInputPressed;
	FVector fireTarget;
	uint8 bIsFireInputHeld;

private:
	UPrimitiveComponent* rigidbody;

	UPROPERTY(Category = "Collision", EditDefaultsOnly)
		float rigidbodyRadius = 10.0f;
	UPROPERTY(Category = "Collision", EditDefaultsOnly)
		float offsetFromGround = 15.0f;

	UPROPERTY(Category = "XY Movement", EditDefaultsOnly)
		float movementSpeed = 10.0f;
	UPROPERTY(Category = "XY Movement", EditDefaultsOnly)
		float maximumMovementSpeed = 15.0f;
	UPROPERTY(Category = "XY Movement", EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float deaccelerator = 0.1f;
	UPROPERTY(Category = "Z Movement", EditDefaultsOnly)
		float fallSpeed = 10.0f;
	UPROPERTY(Category = "Z Movement", EditDefaultsOnly)
		float maximumFallSpeed = 20.0f;

	FVector2D xyVelocity;
	float zVelocity;

	FVector2D CalculateXYVelocity(FVector2D CurrentVelocity, float DeltaTime);

	bool GetIfNearGroundBySweeping(FVector CurrentLocation, FHitResult& HitResult);
};
