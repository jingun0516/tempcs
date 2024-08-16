// Fill out your copyright notice in the Description page of Project Settings.

#include "NameWidget.h"
#include "Components/TextBlock.h"

void UNameWidget::SetName(FText name)
{
	Name->SetText(name);
}
