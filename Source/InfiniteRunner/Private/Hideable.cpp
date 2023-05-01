// Copyright 2023 Joe Binns, All Rights Reserved.


#include "Hideable.h"
#include "TimerManager.h"
#include "Math/Vector.h"

// Sets default values for this component's properties
UHideable::UHideable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHideable::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// Call Hide every frame
	TimerStartTime = FDateTime::Now();
	GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &UHideable::Hide, 0.01f, true);
	// NOTE: In the future, I could just use UKismetSystemLibrary::MoveComponentTo()
	
	UE_LOG(LogTemp, Warning, TEXT("Run"));
}

void UHideable::Hide()
{
	const float Time = (FDateTime::Now() - TimerStartTime).GetTotalSeconds();
	const float Duration = HideCurve->FloatCurve.GetLastKey().Time;
	UE_LOG(LogTemp, Warning, TEXT("Time: %f"), Time);
	UE_LOG(LogTemp, Warning, TEXT("Duration: %f"), Duration);
	if (Time >= Duration)
	{
		GetWorld()->GetTimerManager().ClearTimer(HideTimerHandle);
	}
	
	const float VerticalDisplacement = HideCurve->GetFloatValue(Time);
	GetAttachParent()->SetRelativeLocation(GetUpVector() * VerticalDisplacement);
}


// Called every frame
void UHideable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

