// TerrainManager.cpp
#include "TerrainManager.h"
#include "ChunkActor.h"
#include "Engine/World.h"

ATerrainManager::ATerrainManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATerrainManager::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    const bool bShouldRebuild = bRegenerateNow || bAutoRebuildInEditor;
    if (!bShouldRebuild)
        return;

    bRegenerateNow = false;

    ClearChunks();
    BuildChunks();
}

void ATerrainManager::ClearChunks()
{
    for (AChunkActor* C : SpawnedChunks)
    {
        if (IsValid(C))
        {
            C->Destroy();
        }
    }
    SpawnedChunks.Reset();
}

void ATerrainManager::BuildChunks()
{
    if (!GetWorld())
        return;

    if (!ChunkClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("[TerrainManager] ChunkClass is NULL. Set it in Details."));
        return;
    }

    const float ChunkWorldX = (float)ChunkWidth * BlockSize;
    const float ChunkWorldY = (float)ChunkHeight * BlockSize;

    for (int32 cy = 0; cy < ChunksY; cy++)
    {
        for (int32 cx = 0; cx < ChunksX; cx++)
        {
            const FVector Loc = GetActorLocation() + FVector(cx * ChunkWorldX, cy * ChunkWorldY, 0.f);
            const FRotator Rot = FRotator::ZeroRotator;

            AChunkActor* Chunk = GetWorld()->SpawnActor<AChunkActor>(ChunkClass, Loc, Rot);
            if (!Chunk) continue;

            Chunk->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            Chunk->BuildChunk(ChunkWidth, ChunkHeight, BlockSize, Seed, FIntPoint(cx, cy));

            SpawnedChunks.Add(Chunk);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("[TerrainManager] Built chunks: %d"), SpawnedChunks.Num());
}
