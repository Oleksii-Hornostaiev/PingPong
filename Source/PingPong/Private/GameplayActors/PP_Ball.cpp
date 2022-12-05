// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayActors/PP_Ball.h"
#include "Components/SphereComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/PP_Paddle.h"
#include "Player/PP_PaddleController.h"


APP_Ball::APP_Ball()
{
    bReplicates = true;

    CollisionComp = CreateDefaultSubobject<USphereComponent>("CollisionComp");
    RootComponent = CollisionComp;
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CollisionComp->SetIsReplicated(true);

    VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>("VisualComponent");
    VisualComponent->SetupAttachment(RootComponent);
    VisualComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    VisualComponent->SetIsReplicated(true);
    VisualComponent->SetEnableGravity(false);

    ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
    ProjectileMovementComp->SetUpdatedComponent(RootComponent);
    ProjectileMovementComp->InitialSpeed = 1500.0f;
    ProjectileMovementComp->MaxSpeed = 1500.0f;
    ProjectileMovementComp->bRotationFollowsVelocity = false;
    ProjectileMovementComp->bShouldBounce = true;
    ProjectileMovementComp->Bounciness = 0.3f;
    ProjectileMovementComp->ProjectileGravityScale = 0.0f;
    ProjectileMovementComp->SetIsReplicated(true);

    SetReplicates(true);
}

void APP_Ball::BeginPlay()
{
    Super::BeginPlay();

    SetReplicateMovement(true);
    CollisionComp->OnComponentHit.AddDynamic(this, &APP_Ball::OnHit);
}

void APP_Ball::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
    {
        FVector ReflectedVelocity;
        // Paddle Hit.
        if (const APP_Paddle* Paddle = Cast<APP_Paddle>(OtherActor))
        {
            const APP_PaddleController* PaddleController = Cast<APP_PaddleController>(Paddle->GetController());
            if (PaddleController)
            {
                const float PaddleVelocity = PaddleController->GetPuddleVelocity();

                const FVector Direction = FVector(1.0f, PaddleVelocity, 0.0f);
                ReflectedVelocity = Direction * ProjectileMovementComp->MaxSpeed;
            }
        }
        else
        {
            const FVector BallVelocity = ProjectileMovementComp->Velocity;
            ReflectedVelocity = FVector(BallVelocity.X, -BallVelocity.Y, BallVelocity.Z);
        }
        // If Stopped
        if (ReflectedVelocity.Y == 0.0f)
        {
            const float Random = FMath::RandRange(-1.0f, 1.0f);

            if (Random < 0.0f)
                ReflectedVelocity.Y = -1.0f * ProjectileMovementComp->MaxSpeed;
            else
                ReflectedVelocity.Y = 1.0f * ProjectileMovementComp->MaxSpeed;
        }

        ProjectileMovementComp->Velocity = ReflectedVelocity;
    }
}

