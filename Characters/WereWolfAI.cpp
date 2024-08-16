#include "WereWolfAI.h"
#include "GameFramework/CharacterMovementComponent.h"

AWereWolfAI::AWereWolfAI()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshFinder(L"/Game/werewolf/Mesh/SK_Werewolf_cloth");
	
	if (meshFinder.Succeeded())
		GetMesh()->SetSkeletalMesh(meshFinder.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UAnimInstance> animFinder(L"/Game/Animations/ABP_WereWolf");

	if (animFinder.Succeeded())
		GetMesh()->SetAnimInstanceClass(animFinder.Class);

	SetCharacterMovement();
}

void AWereWolfAI::BeginPlay()
{
	Super::BeginPlay();
}

void AWereWolfAI::SetCharacterMovement()
{
	Super::SetCharacterMovement();

	UCharacterMovementComponent* Comp = GetCharacterMovement();

	Comp->bOrientRotationToMovement = false;
	Comp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	Comp->JumpZVelocity = 700.0f;
	Comp->AirControl = 0.35f;
	Comp->MaxWalkSpeed = 400.0f;

	Comp->BrakingDecelerationWalking = 2000.0f;
	Comp->BrakingDecelerationFalling = 1500.0f;
}
