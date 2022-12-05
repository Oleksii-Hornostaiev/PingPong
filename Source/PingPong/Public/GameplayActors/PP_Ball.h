// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PP_Ball.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PINGPONG_API APP_Ball : public AActor
{
    GENERATED_BODY()

public:
    APP_Ball();

protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* VisualComponent;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovementComp;

public:
    
    UFUNCTION(Client, Reliable)
    void OnHit(UPrimitiveComponent* HitComponent, //
        AActor* OtherActor,                       //
        UPrimitiveComponent* OtherComp,           //
        FVector NormalImpulse,                    //
        const FHitResult& Hit);                   //              
};
