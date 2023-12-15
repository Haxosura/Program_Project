// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_BTTask_ChasingPlayer.h"
#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

UEnemy_BTTask_ChasingPlayer::UEnemy_BTTask_ChasingPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UEnemy_BTTask_ChasingPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Target Location From Blackboard Via The Enemy's Controller
	if (auto* const cont = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		// Move To The Player's Location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, PlayerLocation);

		// Finish With Success
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;

	}
	return EBTNodeResult::Failed;
}}
