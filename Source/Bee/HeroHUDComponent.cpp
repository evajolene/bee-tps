// Copyright 2017 Eva Jolene.

#include "HeroHUDComponent.h"
#include "Blueprint/UserWidget.h"
#include "HeroPawn.h"
#include "HeroAimComponent.h"

UHeroHUDComponent::UHeroHUDComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeroHUDComponent::BeginPlay()
{
	Super::BeginPlay();

	heroPawn = Cast<AHeroPawn>(GetOwner());
	playerController = nullptr;
	if (heroPawn)
	{
		playerController = Cast<APlayerController>(heroPawn->GetController());
	}
	if (playerController == nullptr)
	{
		return;
	}

	UHeroAimComponent* aimComponent = heroPawn->FindComponentByClass<UHeroAimComponent>();
	if (aimComponent)
	{
		AddTickPrerequisiteComponent(aimComponent);
	}

	if (reticleWidgetToAdd)
	{
		reticleWidget = CreateWidget<UUserWidget>(playerController, reticleWidgetToAdd);
		reticleWidget->AddToViewport();
	}
}

void UHeroHUDComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (heroPawn == nullptr || playerController == nullptr)
	{
		return;
	}

	if (reticleWidget)
	{
		FVector2D reticleLocation;
		playerController->ProjectWorldLocationToScreen(heroPawn->fireTarget, reticleLocation);
		reticleWidget->SetPositionInViewport(reticleLocation);
	}
}

