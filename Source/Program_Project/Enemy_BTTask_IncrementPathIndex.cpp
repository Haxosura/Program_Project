// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_BTTask_IncrementPathIndex.h"
#include "Enemy_AIController.h"
#include "Enemy_Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UEnemy_BTTask_IncrementPathIndex::UEnemy_BTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UEnemy_BTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Try and Get the AI Coontroller
	if (auto* const Cont = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		// Try and Get the NPC
		if (auto* const Enemy = Cast<AEnemy_Character>(Cont->GetPawn()))
		{
			// Try and Get the Blackboard		
			if (auto* const BlackComp = OwnerComp.GetBlackboardComponent())
			{
				// Get number of patrol points and min and max indices

				auto const NoOfPoints = Enemy->GetPatrolPath()->Num();
				auto const MinIndex = 0;
				auto const MaxIndex = NoOfPoints - 1;
				auto Index = BlackComp->GetValueAsInt(GetSelectedBlackboardKey());

				// Change direction if we are at the first ar last index if we are in bidirectional mode
				if (bBiDirectional)
				{
					if (Index >= MaxIndex && Direction == EDirectionType::Forward)
					{
						Direction = EDirectionType::Reverse;
					}
					else if (Index == MinIndex && Direction == EDirectionType::Reverse)
					{
						Direction = EDirectionType::Forward;
					}
				}

				// Write new value of index to blackboard
				BlackComp->SetValueAsInt(GetSelectedBlackboardKey(),
					(Direction == EDirectionType::Forward ? ++Index : --Index) % NoOfPoints);

				// Finsh with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;

			}
		}
	}

	return EBTNodeResult::Failed;
}
