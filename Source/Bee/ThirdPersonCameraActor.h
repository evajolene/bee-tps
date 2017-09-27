// Copyright 2017 Eva Jolene.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThirdPersonCameraActor.generated.h"

UCLASS()
class BEE_API AThirdPersonCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(Category = "Settings", BlueprintReadWrite)
		class AHeroPawn* heroPawn;

	UPROPERTY(Category = "Transform", EditDefaultsOnly)
		FVector offset;

	// Sets default values for this actor's properties
	AThirdPersonCameraActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
