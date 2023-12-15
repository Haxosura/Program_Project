// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Enemy_BTTask_ChasingPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAM_PROJECT_API UEnemy_BTTask_ChasingPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UEnemy_BTTask_ChasingPlayer(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};

};
