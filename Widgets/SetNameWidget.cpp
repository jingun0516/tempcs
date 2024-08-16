// Fill out your copyright notice in the Description page of Project Settings.


#include "SetNameWidget.h"
#include "../Characters/Hero.h"

void USetNameWidget::NativeOnInitialized()
{
	NickNameButton->OnClicked.AddDynamic(this, &USetNameWidget::OnNickNameButtonClicked);
	NickNameText->OnTextChanged.AddDynamic(this, &USetNameWidget::OnNickNameChanged);
	OwnerHero = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void USetNameWidget::SetNickName(FText nickName)
{
	NickNameText->SetText(nickName);
}

void USetNameWidget::OnNickNameButtonClicked()
{
	if (!OwnerHero) return;
	OwnerHero->FinishSetNickName();
	SetVisibility(ESlateVisibility::Hidden);
	RemoveFromParent();
}

void USetNameWidget::OnNickNameChanged(const FText& Text)
{
	if (!OwnerHero) return;
	FString NickNameString = Text.ToString();
	UE_LOG(LogTemp, Log, TEXT("NickName Changed: %s"), *NickNameString);
	OwnerHero->SetNickName(Text);
}
