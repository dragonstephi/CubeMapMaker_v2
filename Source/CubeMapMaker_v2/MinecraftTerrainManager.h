// MinecraftTerrainManager.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinecraftTerrainActorv1.h"
#include "MinecraftTerrainManager.generated.h"

UCLASS()
class CUBEMAPMAKER_V2_API AMinecraftTerrainManager : public AActor
{
    GENERATED_BODY()

public:
    AMinecraftTerrainManager();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

public:
    // 🔹 청크 개수
    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunksX = 4;

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunksY = 4;

    // 🔹 청크 단위 크기 (타일 수)
    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunkWidth = 32;

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunkHeight = 32;

    // 🔹 블록/노이즈 공통 설정
    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    float BlockSize = 100.f;

    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    int32 Seed = 12345;

    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    float NoiseScale = 0.1f;

    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    float HeightMultiplier = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    int32 BaseHeight = 15;

    // --- Biome & Water settings ---
    UPROPERTY(EditAnywhere, Category = "Terrain|Biome")
    float BiomeNoiseScale = 0.02f;

    //UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    //float MountainHeightMultiplier = 30.0f;

    UPROPERTY(EditAnywhere, Category = "Terrain|Biome", meta = (ClampMin = "-100.0", ClampMax = "200.0"))
    float BeachHeightMultiplier = 6.0f;

    UPROPERTY(EditAnywhere, Category = "Terrain|Water")
    int32 SeaLevelBlocks = 6;   // 물 높이 (블록 단위)

    UPROPERTY(EditAnywhere, Category = "Terrain|Water", meta = (ClampMin = "0", ClampMax = "4"))
    int32 WaterNeighborRequired = 2; // 주변 몇 칸이 높아야 물 허용할지 (0~4)

    UPROPERTY(EditAnywhere, Category = "Terrain|Water")
    bool bWaterSimpleMode = true;    // 단순 모드: 해변 저지대에 물 많이

    // 🔹 식생 공통 설정
    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    float GrassDensity = 0.3f;

    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    float FlowerDensity = 0.15f;

    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    float TreeDensity = 0.03f;

    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    int32 VegetationSeedOffset = 1000;

    // 🔹 스폰할 청크 클래스
    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    TSubclassOf<AMinecraftTerrainActor> ChunkClass;

    // 집을 어디 청크에 만들지 관리
    UPROPERTY(EditAnywhere, Category = "Terrain|House")
    bool bEnableHouse = true;   // 전체 월드에 집을 만들지 여부

    UPROPERTY(EditAnywhere, Category = "Terrain|House", meta = (EditCondition = "bEnableHouse"))
    int32 HouseChunkX = 0;      // 집이 들어갈 청크 X 인덱스

    UPROPERTY(EditAnywhere, Category = "Terrain|House", meta = (EditCondition = "bEnableHouse"))
    int32 HouseChunkY = 0;      // 집이 들어갈 청크 Y 인덱스

    



private:
    // 이미 스폰된 청크들 (에디터에서 재구성 시 정리용)
    UPROPERTY(Transient)
    TArray<AMinecraftTerrainActor*> SpawnedChunks;
};
