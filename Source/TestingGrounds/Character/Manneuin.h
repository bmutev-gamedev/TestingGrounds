// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Manneuin.generated.h"

class AGun;

UCLASS()
class TESTINGGROUNDS_API AManneuin : public ACharacter
{
	GENERATED_BODY()

    /** Pawn mesh: 1st person view (arms; seen only by self) */
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class USkeletalMeshComponent* FPMesh;

    /** First person camera */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FPCameraComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class UChildActorComponent* FPGun;

public:
	// Sets default values for this character's properties
	AManneuin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void UnPossessed() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
    TSubclassOf<AGun> GunBlueprint;

    /** Fires a projectile. */
    UFUNCTION(BlueprintCallable, Category = "Fire" )
    void PullTrigger();

private:
    AGun* Gun = nullptr;
	
	
};
