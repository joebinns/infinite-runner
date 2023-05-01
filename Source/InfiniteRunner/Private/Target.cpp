// Copyright 2023 Joe Binns, All Rights Reserved.


#include "Target.h"

// Sets default values for this component's properties
UTarget::UTarget()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTarget::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTarget::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

