// Copyright 2017 Eva Jolene.

#include "HeroPawn.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Trace.h"
#include "PickupComponent.h"
#include "WeaponComponent.h"
#include "WeaponActor.h"
#include "GameFramework/Controller.h"
#include "ThirdPersonCameraActor.h"

AHeroPawn::AHeroPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* sphereRigidbody = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = sphereRigidbody;
	sphereRigidbody->RegisterComponent();
	sphereRigidbody->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	sphereRigidbody->SetSphereRadius(rigidbodyRadius);
	sphereRigidbody->SetSimulatePhysics(true);
	sphereRigidbody->SetEnableGravity(false);

	rigidbody = sphereRigidbody;
}

void AHeroPawn::BeginPlay()
{
	Super::BeginPlay();

	movementInput = FVector2D(0, 0);
	yaw = pitch = 0.0f;
	xyVelocity = FVector2D(0, 0);
	zVelocity = 0.0f;
	rigidbody->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	weaponComponent = FindComponentByClass<UWeaponComponent>();
	pickupComponent = FindComponentByClass<UPickupComponent>();
}

void AHeroPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector startingLocation = GetActorLocation();
	FVector actorLocation = startingLocation;

	xyVelocity = CalculateXYVelocity(xyVelocity, DeltaTime);
	
	rigidbody->SetConstraintMode(EDOFMode::XYPlane);
	FVector currentXYVelocity = FVector(xyVelocity.X, xyVelocity.Y, 0.0f) * DeltaTime;
	FHitResult hitResult;
	rigidbody->SetWorldLocation(actorLocation + currentXYVelocity, true, &hitResult);
	
	if (hitResult.bBlockingHit)
	{
		actorLocation = GetActorLocation();
		float distanceLeftToTravel = currentXYVelocity.Size() - (actorLocation - startingLocation).Size();
		if (distanceLeftToTravel > 0.0f)
		{
			FVector wallNormal = hitResult.ImpactNormal;

			FVector playerDirection = currentXYVelocity;
			playerDirection.Normalize();

			//Influence player direction based on where the sphere hit. Helps around corners. 
			playerDirection += actorLocation - hitResult.ImpactPoint;
			playerDirection.Normalize();

			FVector slide = FVector::CrossProduct(FVector::CrossProduct(wallNormal, playerDirection), wallNormal);
			slide.Normalize();
			slide *= distanceLeftToTravel;
			rigidbody->SetWorldLocation(actorLocation + slide, true);
		}
	}

	rigidbody->SetConstraintMode(EDOFMode::None);

	actorLocation = GetActorLocation();

	DrawDebugSphere(
		GetWorld(),
		actorLocation,
		rigidbodyRadius,
		16,
		FColor(0, 155, 155)
	);

	if (GetIfNearGroundBySweeping(actorLocation, hitResult))
	{
		zVelocity = 0.0f;
		actorLocation.Z = hitResult.ImpactPoint.Z + offsetFromGround;
	}
	else
	{
		zVelocity -= DeltaTime * fallSpeed;
		if (zVelocity < -maximumFallSpeed)
		{
			zVelocity = -maximumFallSpeed;
		}
		actorLocation.Z += zVelocity * DeltaTime;
	}
	rigidbody->SetWorldLocation(actorLocation, false);
	actorLocation = GetActorLocation();
	DrawDebugSphere(
		GetWorld(),
		actorLocation,
		rigidbodyRadius,
		16,
		FColor(255, 255, 255)
	);

	DrawDebugSphere(
		GetWorld(),
		actorLocation - FVector(0, 0, offsetFromGround - rigidbodyRadius * 0.375f),
		rigidbodyRadius * 0.375f,
		16,
		FColor(255, 255, 255)
	);
	
	FQuat facingDirection = FQuat::MakeFromEuler(FVector(0.0f, pitch, yaw));
	if (weaponComponent && bIsFireInputHeld)
	{
		weaponComponent->Fire(actorLocation, facingDirection.GetForwardVector());
	}

	if (bIsInteractInputPressed)
	{
		FVector interactLocation = actorLocation;
		interactLocation.Z += interactOffset.Z;
		interactLocation += facingDirection.GetForwardVector() * interactOffset.X + facingDirection.GetRightVector() * interactOffset.Y;
		AWeaponActor* weaponActor = pickupComponent->GetWeaponActorToPickUp(interactLocation, 35.0f);
		PickUpWeapon(weaponActor);
		bIsInteractInputPressed = 0;
	}
}

FVector2D AHeroPawn::CalculateXYVelocity(FVector2D CurrentVelocity, float DeltaTime)
{
	CurrentVelocity *= FMath::Pow(deaccelerator, DeltaTime);

	FVector2D newInput = movementInput;
	float analog = newInput.Size();
	if (analog > 1.0f)
	{
		analog = 1.0f;
	}

	FQuat movementDirection = FQuat::MakeFromEuler(FVector(0.0f, 0.0f, yaw));
	FVector direction = newInput.X * movementDirection.GetRightVector() + newInput.Y * movementDirection.GetForwardVector();
	direction.Normalize();

	CurrentVelocity += (FVector2D)direction * analog * movementSpeed * DeltaTime;
	if (CurrentVelocity.Size() > maximumMovementSpeed)
	{
		CurrentVelocity.Normalize();
		CurrentVelocity *= maximumMovementSpeed;
	}
	return CurrentVelocity;
}

bool AHeroPawn::GetIfNearGroundBySweeping(FVector CurrentLocation, FHitResult& HitResult)
{
	bool bHitGround = UTrace::SweepWorld(this, CurrentLocation, CurrentLocation + FVector(0, 0, -1000.0f), HitResult, rigidbodyRadius * 0.375f);
	return (bHitGround && HitResult.Distance <= offsetFromGround);
}

void AHeroPawn::PickUpWeapon(AWeaponActor* WeaponActor)
{
	bool bIsPickUpValid = (WeaponActor != nullptr && WeaponActor->weaponComponent != nullptr);
	if (weaponComponent == nullptr && bIsPickUpValid)
	{
		weaponComponent = NewObject<UWeaponComponent>(this, WeaponActor->weaponComponent->GetDefaultObject()->GetClass());
		weaponComponent->RegisterComponent();
	}
}