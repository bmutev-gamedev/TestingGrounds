// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // UE_LOG(LogTemp, Warning, TEXT("ChoosingNextWaypoint"))

    // Access PatrolPoints found in the PatrolRouteComponent of the controlled pawn
    APawn* PatrollingGuard = OwnerComp.GetAIOwner()->GetPawn();
    UPatrolRouteComponent* PatrolRoute = PatrollingGuard->FindComponentByClass<UPatrolRouteComponent>();
    if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

    TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();
    if (PatrolPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points"))
        return EBTNodeResult::Failed;
    }

    // Get the Blackboard so we can work with its variables
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

    // Set the new Waypoint to which the guard should go to using the data in PatrolPoints[Index]
    BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

    // Calculate(Cycle) the index of the next PatrolPoint and set it as the new Index
    int32 NextWaypointIndex = (Index + 1) % PatrolPoints.Num();
    BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextWaypointIndex);

    return EBTNodeResult::Succeeded;
}

