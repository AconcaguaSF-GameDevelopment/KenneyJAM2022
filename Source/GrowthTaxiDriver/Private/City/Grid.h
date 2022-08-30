// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"

#include "UObject/NoExportTypes.h"
#include "Grid.generated.h"

class UStreet;
class UBlock;

/**
 * 
 */
UCLASS(Blueprintable)
class UGrid : public UObject
{
	GENERATED_BODY()

	// Properties
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UBlock*> Grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 Dimension = 3;

	// Functions
public:
	UGrid();
	
	UFUNCTION(BlueprintCallable)
	void GenerateGrid();

private:
	UStreet* GetStreetFromNeighbor(const UBlock* block, EBlockNeighborsCardinals neighborCardinal, EBlockSideCardinals blockSideCardinal);
	
	UFUNCTION(BlueprintCallable)
	int ToOneDimensionalIndex(const int i, const int j) const { return i + Dimension * j; }
};
