// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PP_PaddleController.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/PP_Paddle.h"


APP_PaddleController::APP_PaddleController()
{
    PaddleHitVelocity = 0.0f;
}

void APP_PaddleController::BeginPlay()
{
    Super::BeginPlay();
}

void APP_PaddleController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveP1", this, &APP_PaddleController::PaddleMove);
}

float APP_PaddleController::GetPuddleVelocity() const
{
    return PaddleHitVelocity;
}

FVector APP_PaddleController::GetPositionVector() const
{
    return CurrentPosition;
}

void APP_PaddleController::OnRep_PosChange()
{
    FirstPaddle = Cast<APP_Paddle>(K2_GetPawn());
    if (!FirstPaddle) return;
    FirstPaddle->SetActorLocation(CurrentPosition);
}

void APP_PaddleController::PaddleMove(const float Value)
{
    PaddleHitVelocity = Value;
    
    if (Value != 0.0f)
    {
        ServerMoveForward(Value);
    }
}

void APP_PaddleController::ServerMoveForward_Implementation(float Value)
{
    FirstPaddle = Cast<APP_Paddle>(K2_GetPawn());
    if (!FirstPaddle) return;
    FirstPaddle->AddMovementInput(FirstPaddle->GetActorRightVector(), Value, true);
    CurrentPosition = FirstPaddle->GetActorLocation();
}

bool APP_PaddleController::ServerMoveForward_Validate(float Value)
{
    return true;
}

void APP_PaddleController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME( APP_PaddleController, CurrentPosition);
}