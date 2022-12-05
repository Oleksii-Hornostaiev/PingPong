// Fill out your copyright notice in the Description page of Project Settings.


#include "PP_GameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerInput.h"
#include "GameplayActors/PP_Ball.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PP_Paddle.h"
#include "Player/PP_PaddleController.h"
#include "Windows/LiveCoding/Private/External/LC_ClientCommandActions.h"

DEFINE_LOG_CATEGORY(LogPongGame);

APP_GameModeBase::APP_GameModeBase()
{
    PlayerControllerClass = APP_PaddleController::StaticClass();

    FirstPaddleSpawnLocation = FVector::ZeroVector;
    SecondPaddleSpawnLocation = FVector::ZeroVector;
    BallSpawnLocation = FVector::ZeroVector;
    BallSpawnRotation = FRotator::ZeroRotator;
}

void APP_GameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (NewPlayer)
    {
        FVector PaddleLocation;
        FRotator PaddleRotation;
        FActorSpawnParameters SpawnParams;

        PaddlesSpawner(PaddleLocation, PaddleRotation, SpawnParams);

        UGameplayStatics::GetAllActorsOfClass(this, APP_Paddle::StaticClass(), PawnArray);
        if (PawnArray.Num() > 0)
        {
            for (AActor* Actor : PawnArray)
            {
                APP_Paddle* PaddleActor = Cast<APP_Paddle>(Actor);

                if (PaddleActor && !PaddleActor->IsPawnControlled())
                {
                    NewPlayer->Possess(PaddleActor);
                    PaddleActor->SetOwner(NewPlayer);
                }
            }
        }
    }

    if (GetNumPlayers() < 2)
    {
        if (NewPlayer->GetPawn()->GetFName() == FName("PaddleOne"))
        {
            APP_Paddle* PaddleActor = Cast<APP_Paddle>(NewPlayer->GetPawn());
            PaddleActor->AddLogWidget();
        }
    }
    if (GetNumPlayers() == 2)
    {
        BallSpawner(BallSpawnLocation, BallSpawnRotation);
        StartPlay();
    }
}

void APP_GameModeBase::PaddlesSpawner(FVector& PaddleLocation, FRotator& PaddleRotation, FActorSpawnParameters SpawnParams) const
{
    if (PawnArray.Num() == 0)
    {
        SpawnParams.Name = FName("PaddleOne");
        PaddleLocation = FirstPaddleSpawnLocation;
        PaddleRotation = FRotator(0.0f);
    }
    else
    {
        SpawnParams.Name = FName("PaddleTwo");
        PaddleLocation = SecondPaddleSpawnLocation;
        PaddleRotation = FRotator(0.0f, 180.0f, 0.0f);
    }

    GetWorld()->SpawnActor<APP_Paddle>(MyPaddleClass, PaddleLocation, PaddleRotation, SpawnParams);
}

void APP_GameModeBase::BallSpawner(FVector& BallLocation, FRotator& BallRotation) const
{
    BallLocation = BallSpawnLocation;
    GetWorld()->SpawnActor<APP_Ball>(MyBallClass, BallLocation, BallRotation);
}

void APP_GameModeBase::StartPlay()
{
    Super::StartPlay();
}
