// Fill out your copyright notice in the Description page of Project Settings.

#include "MinecraftTerrainManager.h"
#include "Engine/World.h"
#include "EngineUtils.h"

AMinecraftTerrainManager::AMinecraftTerrainManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMinecraftTerrainManager::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (!ChunkClass)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

#if WITH_EDITOR
    // 에디터에서만 동작. (PIE/런타임에 건드리면 값 꼬일 수 있음)
    if (World->WorldType != EWorldType::Editor && World->WorldType != EWorldType::EditorPreview)
    {
        return;
    }
#else
    return;
#endif

    // ✅ 자동 재생성 OFF면: 버튼을 눌렀을 때만 리젠
    if (!bAutoRebuildInEditor && !bRegenerateNow)
    {
        return;
    }

    // 한번 실행하면 다시 꺼서, 에디터 재시작/선택 변경으로 반복 실행 방지
    bRegenerateNow = false;

    // 1) 기존 청크 정리 (이 매니저가 Owner인 모든 청크 파괴)
    for (TActorIterator<AMinecraftTerrainActor> It(World); It; ++It)
    {
        AMinecraftTerrainActor* Chunk = *It;
        if (Chunk && Chunk->GetOwner() == this)
        {
            Chunk->Destroy();
        }
    }

    SpawnedChunks.Empty();

    // 2) 새 청크 스폰 (지연 스폰 방식)
    for (int32 CX = 0; CX < ChunksX; ++CX)
    {
        for (int32 CY = 0; CY < ChunksY; ++CY)
        {
            const int32 ChunkOffsetX = CX * ChunkWidth;
            const int32 ChunkOffsetY = CY * ChunkHeight;

            const FVector ChunkLocation(
                ChunkOffsetX * BlockSize,
                ChunkOffsetY * BlockSize,
                0.f
            );

            const FTransform ChunkTransform(FRotator::ZeroRotator, ChunkLocation);

            FActorSpawnParameters Params;
            Params.Owner = this;
            Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            Params.bDeferConstruction = true;

            AMinecraftTerrainActor* NewChunk = World->SpawnActor<AMinecraftTerrainActor>(
                ChunkClass,
                ChunkTransform,
                Params
            );

            if (!NewChunk)
            {
                continue;
            }

            // 기존 세팅들
            NewChunk->Width = ChunkWidth;
            NewChunk->Height = ChunkHeight;
            NewChunk->BlockSize = BlockSize;
            NewChunk->Seed = Seed;
            NewChunk->NoiseScale = NoiseScale;
            NewChunk->HeightMultiplier = HeightMultiplier;

            NewChunk->GrassDensity = GrassDensity;
            NewChunk->FlowerDensity = FlowerDensity;
            NewChunk->TreeDensity = TreeDensity;
            NewChunk->VegetationSeedOffset = VegetationSeedOffset;

            NewChunk->ChunkOffsetX = ChunkOffsetX;
            NewChunk->ChunkOffsetY = ChunkOffsetY;

            NewChunk->BaseHeight = BaseHeight;
            NewChunk->BiomeNoiseScale = BiomeNoiseScale;
            NewChunk->BeachHeightMultiplier = BeachHeightMultiplier;
            NewChunk->SeaLevelBlocks = SeaLevelBlocks;
            NewChunk->WaterNeighborRequired = WaterNeighborRequired;
            NewChunk->bWaterSimpleMode = bWaterSimpleMode;

            // 이 청크가 집 청크인지 판단
            const bool bThisChunkHasHouse =
                bEnableHouse && (CX == HouseChunkX) && (CY == HouseChunkY);

            NewChunk->bGenerateSampleHouse = bThisChunkHasHouse;

            NewChunk->FinishSpawning(ChunkTransform);
            SpawnedChunks.Add(NewChunk);
        }
    }
}

