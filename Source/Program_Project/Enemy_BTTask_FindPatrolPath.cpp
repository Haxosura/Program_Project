// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_BTTask_FindPatrolPath.h"
#include "Enemy_AIController.h"
#include "Enemy_Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>

UEnemy_BTTask_FindPatrolPath::UEnemy_BTTask_FindPatrolPath(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Path Point");
}

EBTNodeResult::Type UEnemy_BTTask_FindPatrolPath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Attempt to get the enmey's controller
	if (auto* const cont = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		// Attempt to get the blackboard component from the behavior tree
		if (auto* const bc = OwnerComp.GetBlackboardComponent())
		{
			// Get the current patrol path index from the blackboard
			auto const index = bc->GetValueAsInt(GetSelectedBlackboardKey());

			// Get the NPC
			if (auto* enemy = Cast<AEnemy_Character>(cont->GetPawn()))
			{
				// Get the current patrol path vector from the enemy - This is local to the patrol path actor
				auto const Point = enemy->GetPatrolPath()->GetPatrolPoint(index);

				// Convert the local vector to a gloobal point
				auto const GlobalPoint = enemy->GetPatrolPath()->GetActorTransform().TransformPosition(Point);

				if (SearchRandomPoint)
				{
					FNavLocation Loca;

					if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
					{
						// Enenmy Tries To Get to Location Near Player
						if (NavSys->GetRandomPointInNavigableRadius(GlobalPoint, SearchPointRaduis, Loca))
						{
							bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, Loca.Location);

							// Finish with Success
							FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
							return EBTNodeResult::Succeeded;
						}
					}
				}
				else
				{
					bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

					// Finish with Success
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}


			}
		}
	}

	return EBTNodeResult::Failed;
}

FString UEnemy_BTTask_FindPatrolPath::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
