#include "TerrainManager.h"
#include "ChunkActor.h"
#include "Engine/World.h"

ATerrainManager::ATerrainManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATerrainManager::OnConstruction(const FTransform& Transform)
{
    ClearChunks();
    BuildChunks();
}

void ATerrainManager::ClearChunks()
{
    for (AChunkActor* A : SpawnedChunks)
    {
        if (IsValid(A))
        {
            A->Destroy();
        }
    }
    SpawnedChunks.Empty();
}

void ATerrainManager::BuildChunks()
{
    if (!GetWorld() || !ChunkClass) return;

    for (int32 y = 0; y < ChunksY; ++y)
    {
        for (int32 x = 0; x < ChunksX; ++x)
        {
            const FVector Loc = GetActorLocation() + FVector(x * ChunkSpacing, y * ChunkSpacing, 0.f);
            FActorSpawnParameters Params;
            Params.Owner = this;
            Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            AChunkActor* Chunk = GetWorld()->SpawnActor<AChunkActor>(ChunkClass, Loc, FRotator::ZeroRotator, Params);
            if (Chunk)
            {
                SpawnedChunks.Add(Chunk);
            }
        }
    }
}
