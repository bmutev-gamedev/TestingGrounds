// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "Manneuin.h"
#include "../Weapons/Gun.h"
#include "../Weapons/BallProjectile.h"
#include "Animation/AnimInstance.h"


// Sets default values
AManneuin::AManneuin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create a CameraComponent	
    FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FPCameraComponent->SetupAttachment(GetCapsuleComponent());
    FPCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
    FPCameraComponent->bUsePawnControlRotation = true;

    // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
    FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
    FPMesh->SetOnlyOwnerSee(true);
    FPMesh->SetupAttachment(FPCameraComponent);
    FPMesh->bCastDynamicShadow = false;
    FPMesh->CastShadow = false;
    FPMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
    FPMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AManneuin::BeginPlay()
{
	Super::BeginPlay();

    if (!ensure(GunBlueprint)) { return; }
    Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);

    if (IsPlayerControlled())
    {
        Gun->AttachToComponent(FPMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
        Gun->FPAnimInstance = FPMesh->GetAnimInstance();
    }
    else
    {
        Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
        Gun->TPAnimInstance = GetMesh()->GetAnimInstance();
    }

    if (ensure(InputComponent))
    {
        InputComponent->BindAction("Fire", IE_Pressed, this, &AManneuin::PullTrigger);
    }
}

// Called every frame
void AManneuin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AManneuin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AManneuin::UnPossessed()
{
    Super::UnPossessed();
    if (ensure(Gun))
    {
        Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
    }
}

void AManneuin::PullTrigger()
{
    if (!ensure(Gun)) { return; }
    Gun->OnFire();
}

