// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStructs.h"

bool FInputConfig::IsValid() const
{
	return InputAction && InputTag.IsValid();
}
