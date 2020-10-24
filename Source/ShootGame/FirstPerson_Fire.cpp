// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPerson_Fire.h"

// Sets default values
AFirstPerson_Fire::AFirstPerson_Fire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create collision component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("FirstPerson_Fire"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFirstPerson_Fire::OnHit);
	CollisionComponent->InitSphereRadius(15.0f);
	RootComponent = CollisionComponent;

	// 驱动发射物运动
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("CollisionComponentMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	// life length
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AFirstPerson_Fire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstPerson_Fire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirstPerson_Fire::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFirstPerson_Fire::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}