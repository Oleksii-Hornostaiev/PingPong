// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PP_GameModeBase.generated.h"

class APP_Paddle;
class APP_Ball;

DECLARE_LOG_CATEGORY_EXTERN(LogPongGame, Log, All)

/**
 * 
 */
UCLASS()
class PINGPONG_API APP_GameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    APP_GameModeBase();

    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void StartPlay() override;
    TSubclassOf<UUserWidget> GetLogWidget() const { return LogWidget; }

protected:

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> LogWidget;
    
    UPROPERTY(EditAnywhere, Category = "Paddle Class")
    TSubclassOf<APP_Paddle> MyPaddleClass;

    UPROPERTY(EditAnywhere = "Ball Class")
    TSubclassOf<APP_Ball> MyBallClass;
    
    UPROPERTY(EditAnywhere, Category = "Location")
    FVector BallSpawnLocation;

    UPROPERTY(EditAnywhere, Category = "Location")
    FRotator BallSpawnRotation;
    
    UPROPERTY(EditAnywhere, Category = "Location")
    FVector FirstPaddleSpawnLocation;

    UPROPERTY(EditAnywhere, Category = "Location")
    FVector SecondPaddleSpawnLocation;

    UPROPERTY(VisibleAnywhere)
    TArray<AActor*> PawnArray;
    

    void PaddlesSpawner(FVector& PaddleLocation, FRotator& PaddleRotation, FActorSpawnParameters SpawnParams) const;
    void BallSpawner(FVector& BallLocation, FRotator& BallRotation) const;
};
