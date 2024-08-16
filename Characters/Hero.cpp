#include "Hero.h"
#include "BlueprintEditor.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "NPC.h"

#include "../Widgets/NameWidget.h"
#include "../Widgets/SetNameWidget.h"
#include "../Widgets/MainInventoryWidget.h"
#include "../Widgets/ShopAndInvenWidget.h"
#include "../Widgets/ShopWidget.h"
#include "../Components/WeaponComponent.h"
#include "Blueprint/UserWidget.h"

#include "../Weapons/item1.h"
#include "../Weapons/item2.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Components/WidgetComponent.h>

AHero::AHero()
{
	CreateCamera();

	ConstructorHelpers::FObjectFinder<UInputMappingContext> imc(TEXT("/Game/Input/IMC_cs"));

	if (imc.Succeeded())
		KeyMappingContext = imc.Object;  

	ConstructorHelpers::FObjectFinder<UInputAction> jump(TEXT("/Game/Input/Motions/IA_JumpAction"));
	ConstructorHelpers::FObjectFinder<UInputAction> look(TEXT("/Game/Input/Motions/IA_LookAction"));
	ConstructorHelpers::FObjectFinder<UInputAction> move(TEXT("/Game/Input/Motions/IA_MoveAction"));
	ConstructorHelpers::FObjectFinder<UInputAction> first(TEXT("/Game/Input/SelectWeapon/IA_FirstSelect"));
	ConstructorHelpers::FObjectFinder<UInputAction> second(TEXT("/Game/Input/SelectWeapon/IA_SecondSelect"));
	ConstructorHelpers::FObjectFinder<UInputAction> inven(TEXT("/Game/Input/IA_Inven"));

	if (jump.Succeeded())
		JumpAction = jump.Object;
	if (look.Succeeded())
		LookAction = look.Object;
	if (move.Succeeded())
		MoveAction = move.Object;
	if (first.Succeeded())
		FirstWeaponSelect = first.Object;
	if (second.Succeeded())
		SecondWeaponSelect = second.Object;
	if (inven.Succeeded())
		OpenInven = inven.Object;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn"));
	if(mesh.Succeeded())
		GetMesh()->SetSkeletalMesh(mesh.Object);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	bUseControllerRotationYaw = false;
	NameWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Name Widget"));

	if (NameWidgetComp)
	{
		ConstructorHelpers::FClassFinder<UNameWidget> nameFinder(TEXT("/Game/Widgets/WB_Name"));
		if (nameFinder.Succeeded())
			NameClass = nameFinder.Class;
		if (!NameClass) return;
		NameWidgetComp->SetWidgetClass(NameClass);
		NameWidgetComp->SetupAttachment(GetMesh());
		NameWidgetComp->SetRelativeLocation(FVector(0, 0, 200.f)); // 위치 설정
		NameWidgetComp->SetRelativeRotation(FRotator(0, 90.f, 0)); // 회전 설정
		NameWidgetComp->SetDrawSize(FVector2D(300, 200)); // 크기 설정
		NameWidgetComp->SetWidgetSpace(EWidgetSpace::Screen); // 공간 설정
		NameWidgetComp->bAutoActivate = true; // 자동 활성화
	}

	ConstructorHelpers::FClassFinder<USetNameWidget> setnameFinder(TEXT("/Game/Widgets/WB_SetName"));
	if (setnameFinder.Succeeded())
		SetNameClass = setnameFinder.Class;
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");

	ConstructorHelpers::FClassFinder<UMainInventoryWidget> invenFinder(TEXT("/Game/Widgets/WB_MainInventory"));
	if (invenFinder.Succeeded())
		InvenClass = invenFinder.Class;

	ConstructorHelpers::FClassFinder<UShopAndInvenWidget> sinvenFinder(TEXT("/Game/Widgets/WB_ShopAndInven"));
	if (sinvenFinder.Succeeded())
		ShopAndInvenClass = sinvenFinder.Class;

	ConstructorHelpers::FClassFinder<UAnimInstance> animFinder(L"/Game/Characters/Mannequins/Animations/ABP_Quinn");

	if (animFinder.Succeeded())
		GetMesh()->SetAnimInstanceClass(animFinder.Class);

	ConstructorHelpers::FClassFinder<UShopWidget> shop(TEXT("/Game/Widgets/WB_Shop"));
	if (shop.Succeeded())
		ShopClass = shop.Class;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHero::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AHero::OnOverlapEnd);

	SetCharacterMovement();
}

void AHero::FinishSetNickName()
{
	FString NickNameString = NickName.ToString();
	UE_LOG(LogTemp, Log, TEXT("Current NickName: %s"), *NickNameString);
	if (!NameWidget) return;
	NameWidget->SetName(NickName);
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer());

		if (SubSystem != nullptr)
			SubSystem->AddMappingContext(KeyMappingContext, 0);
	}

	if (SetNameClass) {
		SetNameWidget = CreateWidget<USetNameWidget>(GetWorld(), SetNameClass);
		if (!SetNameWidget) return;
		SetNameWidget->AddToViewport();
		SetNameWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (InvenClass) {
		InvenWidget = CreateWidget<UMainInventoryWidget>(GetWorld(), InvenClass);
		if (!InvenWidget) return;
		InvenWidget->AddToViewport(0);
		InvenWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (ShopAndInvenClass) {
		ShopAndInvenWidget = CreateWidget<UShopAndInvenWidget>(GetWorld(), ShopAndInvenClass);
		if (!ShopAndInvenWidget) return;
		ShopAndInvenWidget->AddToViewport(0);
		ShopAndInvenWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ShopClass) {
		ShopWidget = CreateWidget<UShopWidget>(GetWorld(), ShopClass);
		if (!ShopWidget) return;
		ShopWidget->AddToViewport(0);
		ShopWidget->SetVisibility(ESlateVisibility::Hidden);

		Aitem1* item1 = GetWorld()->SpawnActor<Aitem1>();
		Aitem2* item2 = GetWorld()->SpawnActor<Aitem2>();
		ShopWidget->SetItem(0, item1);
		ShopWidget->SetItem(1, item2);
		ShopAndInvenWidget->SetItem(0, item1);
		ShopAndInvenWidget->SetItem(1, item2);
	}

	NameWidget = Cast<UNameWidget>(NameWidgetComp->GetUserWidgetObject());
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHero::Move);				
		EnhancedInputComponent->BindAction(OpenInven, ETriggerEvent::Triggered, this, &AHero::DoOpenInven);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHero::Look);

		EnhancedInputComponent->BindAction(FirstWeaponSelect, ETriggerEvent::Triggered, this, &AHero::DoFirstSelect);
		EnhancedInputComponent->BindAction(SecondWeaponSelect, ETriggerEvent::Triggered, this, &AHero::DoSecondSelect);

	}
}

void AHero::SetCharacterMovement()
{
	Super::SetCharacterMovement();

	UCharacterMovementComponent* Comp = GetCharacterMovement();

	Comp->bOrientRotationToMovement = true;
	Comp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	Comp->JumpZVelocity = 700.0f;
	Comp->AirControl = 0.35f;
	Comp->MaxWalkSpeed = 600.0f;

	Comp->BrakingDecelerationWalking = 2000.0f;
	Comp->BrakingDecelerationFalling = 1500.0f;
}

void AHero::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

		const FVector FwdDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(FwdDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AHero::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput(LookAxisVector.Y);
		AddControllerYawInput(LookAxisVector.X);
	}
}

void AHero::CreateCamera()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	CameraArm->SetupAttachment(RootComponent);

	CameraArm->TargetArmLength = 400.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraArm);
	Camera->bUsePawnControlRotation = false;
}

void AHero::DoFirstSelect()
{
	if (DFirstWeaponSelect.IsBound())
	{
		UE_LOG(LogTemp, Log, TEXT("FirstSelect"));
		DFirstWeaponSelect.Broadcast();
	}
}

void AHero::DoSecondSelect()
{
	if (DSecondWeaponSelect.IsBound())
	{
		UE_LOG(LogTemp, Log, TEXT("SecondSelect"));
		DSecondWeaponSelect.Broadcast();
	}
}

void AHero::DoOpenInven()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (IsShopOpen())
	{
		DoOpenShopAndInven();
		return;
	}
	
	if (InvenWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		InvenWidget->SetVisibility(ESlateVisibility::Visible);
		
		if (PlayerController)
		{
			FInputModeUIOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			InvenWidget->SetKeyboardFocus();
		}
	}
}

void AHero::DoOpenShopAndInven()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!ShopAndInvenWidget) return;

	if (IsShopOpen()) ShopWidget->SetVisibility(ESlateVisibility::Hidden);

	if (ShopAndInvenWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		ShopAndInvenWidget->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Log, TEXT("qwerqwer"));
		if (PlayerController)
		{
			FInputModeUIOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			ShopAndInvenWidget->SetKeyboardFocus();
		}
	}
	else
	{
		ShopAndInvenWidget->SetVisibility(ESlateVisibility::Hidden);

		if (PlayerController)
		{
			FInputModeGameAndUI InputMode;
			PlayerController->SetInputMode(InputMode);
		}
	}
}

void AHero::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ANPC>(OtherActor)) return;

	if (IsInvenOpen())
	{
		DoOpenShopAndInven();
		SetShopOpen(true);
		return;
	}
	SetShopOpen(true);
	if (ShopWidget)
	{
		ShopWidget->SetVisibility(ESlateVisibility::Visible);
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FInputModeGameAndUI InputMode;
		PlayerController->SetInputMode(InputMode);
		ShopWidget->SetFocus();
	}
}

void AHero::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//ShopWidget->SetVisibility(ESlateVisibility::Hidden);
	SetShopOpen(false);
}
