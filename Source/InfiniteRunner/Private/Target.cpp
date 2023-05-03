// Copyright 2023 Joe Binns, All Rights Reserved.


#include "Target.h"
#include "PlayablePlayerState.h"

// Sets default values for this component's properties
UTarget::UTarget()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
	this->OnComponentBeginOverlap.AddDynamic(this, &UTarget::OnOverlapBegin);
	this->OnComponentEndOverlap.AddDynamic(this, &UTarget::OnOverlapEnd);
}

// Called when the game starts
void UTarget::BeginPlay()
{
	Super::BeginPlay();

	NextRow = Cast<UHideable>(NextRowReference.GetComponent(GetOwner()));
}

void UTarget::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Target Encountered"));

	if (!NextRow) return;
	if (FMath::RandRange(1, 100) <= 50  ? true : false) return; // Only act 50% of the time
	NextRow->StartHide();

	UE_LOG(LogTemp, Warning, TEXT("Start Hide"));
}

void UTarget::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


// Called every frame
void UTarget::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

