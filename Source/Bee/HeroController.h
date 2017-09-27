// Copyright 2017 Eva Jolene.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroController.generated.h"

UCLASS()
class BEE_API AHeroController : public APlayerController
{
	GENERATED_BODY()

	class AHeroPawn* heroPawn;
public:
	AHeroController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	void OnXAxisMovementInput(float InputAmount);
	void OnYAxisMovementInput(float InputAmount);
	void OnInteractInput();
	void OnWeaponFireInput();
	void OnWeaponFireInputReleased();

	UPROPERTY(Category = "Controls", EditDefaultsOnly)
		float yawLookSpeed = 2.5f;
	UPROPERTY(Category = "Controls", EditDefaultsOnly)
		float pitchLookSpeed = 2.375f;
};
