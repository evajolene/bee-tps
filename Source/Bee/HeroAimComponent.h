// Copyright 2017 Eva Jolene.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeroAimComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEE_API UHeroAimComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	class AHeroPawn* heroPawn;

public:	
	// Sets default values for this component's properties
	UHeroAimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
