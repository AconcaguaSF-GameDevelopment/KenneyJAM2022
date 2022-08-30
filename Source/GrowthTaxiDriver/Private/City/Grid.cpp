// Fill out your copyright notice in the Description page of Project Settings.

#include "City/Grid.h"

#include "Block.h"
#include "Street.h"

UGrid::UGrid()
{
    Grid.Reserve(Dimension * Dimension);
}

void UGrid::GenerateGrid()
{
    // Generate the whole grid
    for (int i = 0; i < Dimension; ++i)
    {
        for (int j = 0; j < Dimension; ++j)
        {
            UBlock* newBlock = NewObject<UBlock>();
            Grid.Add(newBlock);
        }
    }

    // Traverse all blocks
    for (int i = 0; i < Dimension; ++i)
    {
        for (int j = 0; j < Dimension; ++j)
        {
            UBlock* currentBlock = Grid[ToOneDimensionalIndex(i, j)];
            UBlock* currentNeighbor = nullptr;

            if (j > 0)
            {
                // First Row
                if (i > 0)
                {
                    currentNeighbor = Grid[ToOneDimensionalIndex(i - 1, j - 1)];
                    currentBlock->Neighbors.Insert(currentNeighbor,
                                                   UBlock::NeighborCardinalToIndex(
                                                       EBlockNeighborsCardinals::NORTH_WEST));
                }

                currentNeighbor = Grid[ToOneDimensionalIndex(i, j - 1)];
                currentBlock->Neighbors.Insert(currentNeighbor,
                                               UBlock::NeighborCardinalToIndex(EBlockNeighborsCardinals::NORTH));

                if (i < Dimension - 1)
                {
                    currentNeighbor = Grid[ToOneDimensionalIndex(i + 1, j - 1)];
                    currentBlock->Neighbors.Insert(currentNeighbor,
                                                   UBlock::NeighborCardinalToIndex(
                                                       EBlockNeighborsCardinals::NORTH_EAST));
                }
            }

            // Same Row
            if (i > 0)
            {
                currentNeighbor = Grid[ToOneDimensionalIndex(i - 1, j)];
                currentBlock->Neighbors.Insert(currentNeighbor,
                                               UBlock::NeighborCardinalToIndex(EBlockNeighborsCardinals::WEST));
            }
            if (i < Dimension - 1)
            {
                currentNeighbor = Grid[ToOneDimensionalIndex(i + 1, j)];
                currentBlock->Neighbors.Insert(currentNeighbor,
                                               UBlock::NeighborCardinalToIndex(EBlockNeighborsCardinals::EAST));
            }

            if (j < Dimension - 1)
            {
                // Bottom Row
                if (i > 0)
                {
                    currentNeighbor = Grid[ToOneDimensionalIndex(i - 1, j + 1)];
                    currentBlock->Neighbors.Insert(currentNeighbor,
                                                   UBlock::NeighborCardinalToIndex(
                                                       EBlockNeighborsCardinals::SOUTH_WEST));
                }

                currentNeighbor = Grid[ToOneDimensionalIndex(i, j + 1)];
                currentBlock->Neighbors.Insert(currentNeighbor,
                                               UBlock::NeighborCardinalToIndex(EBlockNeighborsCardinals::SOUTH));

                if (i < Dimension - 1)
                {
                    currentNeighbor = Grid[ToOneDimensionalIndex(i + 1, j + 1)];
                    currentBlock->Neighbors.Insert(currentNeighbor,
                                                   UBlock::NeighborCardinalToIndex(
                                                       EBlockNeighborsCardinals::SOUTH_EAST));
                }
            }

            // Look for street connections and assign them
            for (const auto& currentStreet : currentBlock->Streets)
            {
                UStreet* connection = nullptr;

                switch (currentStreet->BlockSide)
                {
                case EBlockSideCardinals::NORTH:
                    {
                        connection = GetStreetFromNeighbor(currentBlock,
                                                           EBlockNeighborsCardinals::NORTH_EAST,
                                                           EBlockSideCardinals::WEST);
                        if (connection != nullptr)
                        {
                            if (connection != nullptr)
                            {
                                currentStreet->Connections.Add(connection);
                            }
                        }

                        connection = GetStreetFromNeighbor(currentBlock,
                                                           EBlockNeighborsCardinals::EAST,
                                                           EBlockSideCardinals::NORTH);
                        if (connection != nullptr)
                        {
                            currentStreet->Connections.Add(connection);
                        }
                        break;
                    }
                case EBlockSideCardinals::EAST:
                    {
                        connection = GetStreetFromNeighbor(currentBlock,
                                                           EBlockNeighborsCardinals::SOUTH_EAST,
                                                           EBlockSideCardinals::NORTH);
                        if (connection != nullptr)
                        {
                            currentStreet->Connections.Add(connection);
                        }

                        connection = GetStreetFromNeighbor(currentBlock,
                                                           EBlockNeighborsCardinals::SOUTH,
                                                           EBlockSideCardinals::EAST);
                        if (connection != nullptr)
                        {
                            currentStreet->Connections.Add(connection);
                        }
                        break;
                    }

                case EBlockSideCardinals::SOUTH:
                    {
                        connection = GetStreetFromNeighbor(currentBlock,
                                                           EBlockNeighborsCardinals::SOUTH_WEST,
                                                           EBlockSideCardinals::EAST);
                        if (connection != nullptr)
                        {
                            currentStreet->Connections.Add(connection);
                        }

                        connection = GetStreetFromNeighbor(currentBlock,
                                                           EBlockNeighborsCardinals::WEST,
                                                           EBlockSideCardinals::SOUTH);
                        if (connection != nullptr)
                        {
                            currentStreet->Connections.Add(connection);
                        }
                        break;
                    }
                case EBlockSideCardinals::WEST:
                    {
                        connection = GetStreetFromNeighbor(currentBlock,
                                                           EBlockNeighborsCardinals::NORTH_WEST,
                                                           EBlockSideCardinals::SOUTH);
                        if (connection != nullptr)
                        {
                            currentStreet->Connections.Add(connection);
                        }

                        connection = GetStreetFromNeighbor(currentBlock,
                                                           EBlockNeighborsCardinals::NORTH,
                                                           EBlockSideCardinals::WEST);
                        if (connection != nullptr)
                        {
                            currentStreet->Connections.Add(connection);
                        }
                        break;
                    }
                }
            }
        } // Block grid for-loop
    }
}

UStreet* UGrid::GetStreetFromNeighbor(const UBlock* block,
                                      EBlockNeighborsCardinals neighborCardinal,
                                      EBlockSideCardinals blockSideCardinal)
{
    const uint8 neighborIndex = UBlock::NeighborCardinalToIndex(neighborCardinal);
    const uint8 streetIndex = UBlock::BlockSideCardinalToIndex(blockSideCardinal);

    const UBlock* possibleNeighbor = block->Neighbors[neighborIndex];

    if (possibleNeighbor != nullptr)
    {
        return possibleNeighbor->Streets[streetIndex];
    }
    return nullptr;
}
