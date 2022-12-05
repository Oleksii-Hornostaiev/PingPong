// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PP_Paddle.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PP_PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayActors/PP_Ball.h"

DEFINE_LOG_CATEGORY(LogPaddle)

APP_Paddle::APP_Paddle()
{
    bReplicates = true;

    CollisionComp = CreateDefaultSubobject<UBoxComponent>("CollisionComp");
    RootComponent = CollisionComp;
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>("VisualComponent");
    VisualComponent->SetupAttachment(RootComponent);
    VisualComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    VisualComponent->SetCollisionObjectType(ECC_Pawn);

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
    SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
    CameraComp->SetupAttachment(SpringArmComp);

    MovementComp = CreateDefaultSubobject<UPP_PawnMovementComponent>("MovementComp");
    MovementComp->UpdatedComponent = RootComponent;
    MovementComp->SetIsReplicated(true);
}

void APP_Paddle::BeginPlay()
{
    Super::BeginPlay();
    SetReplicateMovement(true);
}

void APP_Paddle::AddLogWidget_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("This message will appear on the screen!"));
}


UPawnMovementComponent* APP_Paddle::GetMovementComponent() const
{
    return MovementComp;
}

UStaticMeshComponent* APP_Paddle::GetStaticMeshComponent() const
{
    return VisualComponent;
}
