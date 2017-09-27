// Copyright 2017 Eva Jolene.

#include "HeroController.h"
#include "HeroPawn.h"

AHeroController::AHeroController(const FObjectInitializer& ObjectInitializer) : APlayerController(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHeroController::BeginPlay()
{
	Super::BeginPlay();

	APawn* pawn = GetPawn();
	if (pawn != nullptr)
	{
		heroPawn = Cast<AHeroPawn>(pawn);
	}
}

void AHeroController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("XAxisMovement", this, &AHeroController::OnXAxisMovementInput);
	InputComponent->BindAxis("YAxisMovement", this, &AHeroController::OnYAxisMovementInput);
	InputComponent->BindAction("InteractWithThings", EInputEvent::IE_Pressed, this, &AHeroController::OnInteractInput);
	InputComponent->BindAction("FireWeapon", EInputEvent::IE_Pressed, this, &AHeroController::OnWeaponFireInput);
	InputComponent->BindAction("FireWeapon", EInputEvent::IE_Released, this, &AHeroController::OnWeaponFireInputReleased);
}

void AHeroController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (heroPawn == nullptr)
	{
		return;
	}

	float mouseX, mouseY;
	if (GetMousePosition(mouseX, mouseY))
	{
		int screenWidth, screenHeight;
		GetViewportSize(screenWidth, screenHeight);
		int centerX = (screenWidth / 2);
		int centerY = (screenHeight / 2);

		heroPawn->yaw += (mouseX - centerX) * yawLookSpeed * DeltaTime;
		heroPawn->pitch += (mouseY - centerY) * pitchLookSpeed * DeltaTime;
		heroPawn->pitch = FMath::Clamp(heroPawn->pitch, -90.0f, 90.0f);

		SetMouseLocation(centerX, centerY);
	}
}

void AHeroController::OnXAxisMovementInput(float InputAmount)
{
	if (heroPawn != nullptr)
	{
		heroPawn->movementInput.X = InputAmount;
	}
}

void AHeroController::OnYAxisMovementInput(float InputAmount)
{
	if (heroPawn != nullptr)
	{
		heroPawn->movementInput.Y = InputAmount;
	}
}

void AHeroController::OnInteractInput()
{
	if (heroPawn != nullptr)
	{
		heroPawn->bIsInteractInputPressed = 1;
	}
}

void AHeroController::OnWeaponFireInput()
{
	if (heroPawn != nullptr)
	{
		heroPawn->bIsFireInputHeld = 1;
	}
}

void AHeroController::OnWeaponFireInputReleased()
{
	if (heroPawn != nullptr)
	{
		heroPawn->bIsFireInputHeld = 0;
	}
}