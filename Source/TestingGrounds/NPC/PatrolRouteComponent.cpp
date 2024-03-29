// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "PatrolRouteComponent.h"


// Sets default values for this component's properties
UPatrolRouteComponent::UPatrolRouteComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

TArray<AActor*> UPatrolRouteComponent::GetPatrolPoints() const
{
    return PatrolPoints;
}
