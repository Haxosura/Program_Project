// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "Program_ProjectCharacter.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemy_AIController::AEnemy_AIController()
{
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AEnemy_AIController::BeginPlay()
{
    Super::BeginPlay();

    if (IsValid(BehaviorTree.Get()))
    {
        RunBehaviorTree(BehaviorTree.Get());
        BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
    }
}

void AEnemy_AIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
    {
        Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
    }
}

void AEnemy_AIController::SetupPerceptionSystem()
{
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    if (SightConfig)
    {
        SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
        SightConfig->SightRadius = 500.f;
        SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
        SightConfig->PeripheralVisionAngleDegrees = 90.f;
        SightConfig->SetMaxAge(5.f);
        SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

        GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
        GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::OnTargetDetected);
        GetPerceptionComponent()->ConfigureSense(*SightConfig);
    }
}

void AEnemy_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
    if (auto* const ch = Cast<AProgram_ProjectCharacter>(Actor))
    {
        GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player Seen"));
    }
}
