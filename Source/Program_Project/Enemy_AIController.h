// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class PROGRAM_PROJECT_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
    AEnemy_AIController();

protected:
    virtual void BeginPlay();
    virtual void OnPossess(APawn* InPawn);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true));
    TObjectPtr<UBehaviorTree> BehaviorTree;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true));
    TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true));
    TObjectPtr<UBlackboardComponent> BlackboardComponent;

};
