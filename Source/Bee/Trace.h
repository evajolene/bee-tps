// Copyright 2017 Eva Jolene.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Trace.generated.h"

UCLASS()
class BEE_API UTrace : public UObject
{
	GENERATED_BODY()

public:
	static bool SweepWorld(AActor* Tracer, FVector Start, FVector End, FHitResult& HitResult, float Radius = 0.0f);
};
