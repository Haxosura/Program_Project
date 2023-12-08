// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true));
    TObjectPtr<UBehaviorTree> BehaviorTree;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true));
    TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true));
    TObjectPtr<UBlackboardComponent> BlackboardComponent;

private:
    class UAISenseConfig_Sight* SightConfig;

    void SetupPerceptionSystem();

    UFUNCTION()
    void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
};