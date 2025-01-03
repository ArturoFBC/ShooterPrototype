// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"
#include "Gun.h"
#include "TPSGameModeBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

bool ATPSCharacter::IsDead() const
{
    return Health <= 0;
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ATPSCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ATPSCharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed,this, &ATPSCharacter::Shoot);
}

float ATPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    float DamageToApply= Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= DamageToApply;
	if (Health < 0)
		Health = 0;

	UE_LOG(LogTemp, Warning, TEXT("%f"), Health);
	if (IsDead())
	{
		ATPSGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATPSGameModeBase>();
		if (GameMode != nullptr)
			GameMode->PawnKilled(this);

		DetachFromControllerPendingDestroy();

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

void ATPSCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ATPSCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ATPSCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * PitchRate * GetWorld()->GetDeltaSeconds());
}

void ATPSCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * YawRate * GetWorld()->GetDeltaSeconds());
}

void ATPSCharacter::Shoot()
{
	Gun->PullTrigger();
}

float ATPSCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}
