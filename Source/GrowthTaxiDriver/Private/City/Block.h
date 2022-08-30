// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Block.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBlockSideCardinals : uint8
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
};
ENUM_RANGE_BY_FIRST_AND_LAST(EBlockSideCardinals, EBlockSideCardinals::NORTH, EBlockSideCardinals::WEST);

UENUM(BlueprintType)
enum class EBlockNeighborsCardinals : uint8
{
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST
};
ENUM_RANGE_BY_FIRST_AND_LAST(EBlockNeighborsCardinals, EBlockNeighborsCardinals::NORTH, EBlockNeighborsCardinals::NORTH_WEST);

class UStreet;

/**
 * 
 */
UCLASS(Blueprintable)
class UBlock : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UBlock*> Neighbors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UStreet*> Streets;

private:

public:
	UBlock();
	
	UFUNCTION(BlueprintCallable)
	static int NeighborCardinalToIndex(const EBlockNeighborsCardinals cardinal) { return static_cast<int>(cardinal); }

	UFUNCTION(BlueprintCallable)
	static int BlockSideCardinalToIndex(const EBlockSideCardinals cardinal) { return static_cast<int>(cardinal); }
};
