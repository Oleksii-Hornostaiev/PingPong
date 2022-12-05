// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PP_PaddleController.generated.h"


class APP_Paddle;
class UPP_PawnMovementComponent;
/**
 * 
 */
UCLASS()
class PINGPONG_API APP_PaddleController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void SetupInputComponent() override;
    virtual float GetPuddleVelocity() const;
    virtual FVector GetPositionVector() const;

protected:
    UPROPERTY(Transient, ReplicatedUsing = OnRep_PosChange)
    FVector CurrentPosition;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    APP_Paddle* FirstPaddle;
    
    UPROPERTY(VisibleAnywhere)
    float PaddleHitVelocity;
    
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerMoveForward(float Value);

    UFUNCTION()
    void OnRep_PosChange();
    
    UFUNCTION()
    void PaddleMove(const float Value);
    
    virtual void BeginPlay() override;

public:
    APP_PaddleController();
};
