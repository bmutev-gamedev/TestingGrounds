// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
    int32 NumberOfSpawns = FMath::RandRange(MinSpawn, MaxSpawn);
    for (size_t i = 0; i < NumberOfSpawns; i++)
    {
        FVector SpawnPoint;

        float RandomScale = FMath::RandRange(MinScale, MaxScale);
        bool Found = FindEmptyLocation(SpawnPoint, Radius * RandomScale);
        if (Found)
        {
            float RandomRotation = FMath::RandRange(-180.0f, 180.0f);
            PlaceActor(ToSpawn, SpawnPoint, RandomRotation, RandomScale);
        }
    }
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
    FVector MinPoint(0, -2000, 0);
    FVector MaxPoint(4000, 2000, 0);

    const int32 Limit = 100;

    for (size_t i = 0; i < Limit; i++)
    {
        FVector CandidateLocation = FMath::RandPointInBox(FBox(MinPoint, MaxPoint));
        if (CanSpawnAtLocation(CandidateLocation, Radius))
        {
            OutLocation = CandidateLocation;
            return true;
        }
    }

    return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale)
{
    AActor* Spawned = GetWorld()->SpawnActor(ToSpawn);
    Spawned->SetActorRelativeLocation(SpawnPoint);
    Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    Spawned->SetActorRotation(FRotator(0, Rotation, 0));
    Spawned->SetActorScale3D(FVector(Scale));
}
// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
    FHitResult HitResult;

    FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
    bool HasHit = GetWorld()->SweepSingleByChannel(
                                    HitResult,
                                    GlobalLocation,
                                    GlobalLocation,
                                    FQuat::Identity,
                                    ECollisionChannel::ECC_GameTraceChannel2,
                                    FCollisionShape::MakeSphere(Radius)
                                );

    return !HasHit;
}

void ATile::SpawnFoliage()
{

}