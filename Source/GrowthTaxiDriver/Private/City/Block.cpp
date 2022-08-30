// Fill out your copyright notice in the Description page of Project Settings.


#include "City/Block.h"

#include "Street.h"

UBlock::UBlock()
{
	Streets.Reserve(4);
	Neighbors.SetNumZeroed(8);
	
	UStreet* previous = nullptr;

	for (const EBlockSideCardinals CardinalPoint : TEnumRange<EBlockSideCardinals>())
	{
		UStreet* newStreet = NewObject<UStreet>();
		
		newStreet->BlockSide = CardinalPoint;
		
		Streets.Add(newStreet);
		
		if (CardinalPoint != EBlockSideCardinals::NORTH)
		{
			previous->Connections.Add(newStreet);

			if (CardinalPoint == EBlockSideCardinals::WEST)
			{
				newStreet->Connections.Add(Streets[static_cast<int>(EBlockSideCardinals::NORTH)]);
			}
		}

		previous = newStreet;
	}
}
