// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Street.generated.h"

enum class EBlockSideCardinals : uint8;
/**
 * 
 */
UCLASS(Blueprintable)
class UStreet : public UObject
{
	GENERATED_BODY()
	
	// Properties
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ClampMin="0", ClampMax="1"))
	float Weight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EBlockSideCardinals BlockSide;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UStreet*> Connections;

protected:

private:


	// Functions
public:
	UStreet();

protected:

private:

};
