// Copyright 2017 Eva Jolene.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeroHUDComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEE_API UHeroHUDComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	class AHeroPawn* heroPawn;
	APlayerController* playerController;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UUserWidget> reticleWidgetToAdd;

	UUserWidget* reticleWidget;

public:	
	UHeroHUDComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
