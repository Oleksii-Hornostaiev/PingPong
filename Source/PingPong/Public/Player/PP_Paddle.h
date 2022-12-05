// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PP_PawnMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "PP_Paddle.generated.h"

class UBoxComponent;
class UCameraComponent;
class USpringArmComponent;
class UPP_CharacterMovementComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogPaddle, Log, All)

UCLASS()
class PINGPONG_API APP_Paddle : public APawn
{
    GENERATED_BODY()

public:
    APP_Paddle();

protected:
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* VisualComponent;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UCameraComponent* CameraComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPP_PawnMovementComponent* MovementComp;

public:
    
    UFUNCTION(Client, Reliable)
    void AddLogWidget();

    virtual UPawnMovementComponent* GetMovementComponent() const override;
    UStaticMeshComponent* GetStaticMeshComponent() const;

    virtual void BeginPlay() override;
};
