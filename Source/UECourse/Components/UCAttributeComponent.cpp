// Fill out your copyright notice in the Description page of Project Settings.
#include "UCAttributeComponent.h"

UUCAttributeComponent::UUCAttributeComponent()
{
	Health = 100.f;
}

bool UUCAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	
	return true;
}

