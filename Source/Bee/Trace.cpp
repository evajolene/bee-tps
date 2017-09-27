// Copyright 2017 Eva Jolene.

#include "Trace.h"
#include "Engine/World.h"

bool UTrace::SweepWorld(AActor* Tracer, FVector Start, FVector End, FHitResult& HitResult, float Radius)
{
	TArray<FHitResult> hitResults;
	bool bHasHit;
	if (Radius <= 0.0f)
	{
		bHasHit = Tracer->GetWorld()->LineTraceMultiByObjectType
		(
			hitResults, Start, End,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
			FCollisionQueryParams(FName(NAME_None), true, Tracer)
		);
	}
	else
	{
		bHasHit = Tracer->GetWorld()->SweepMultiByObjectType
		(
			hitResults, Start, End, FQuat(),
			FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
			FCollisionShape::MakeSphere(Radius),
			FCollisionQueryParams(FName(NAME_None), true, Tracer)
		);
	}

	if (bHasHit)
	{
		HitResult = *FHitResult::GetFirstBlockingHit(hitResults);
	}

	return (bHasHit && HitResult.GetActor() != nullptr);
}
