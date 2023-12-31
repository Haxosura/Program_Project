// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "PatrolPath.h"
#include "GameFramework/Character.h"
#include "Enemy_Character.generated.h"

UCLASS()
class PROGRAM_PROJECT_API AEnemy_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Character();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    APatrolPath* GetPatrolPath() const;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
    APatrolPath* PatrolPath;
};
