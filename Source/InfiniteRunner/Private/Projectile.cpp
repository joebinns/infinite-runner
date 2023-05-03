// Copyright 2023 Joe Binns, All Rights Reserved.


#include "Projectile.h"

UProjectile::UProjectile()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UProjectile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Move(DeltaTime);
}

void UProjectile::Move(float DeltaTime)
{
	TimeElapsed += DeltaTime;
	SetRelativeLocation(FMath::Sin(TimeElapsed * Frequency) * GetRightVector() * Amplitude);
}