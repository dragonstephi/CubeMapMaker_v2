// TerrainManager.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainManager.generated.h"

class AChunkActor;

UCLASS()
class CUBEMAPMAKER_V2_API ATerrainManager : public AActor
{
    GENERATED_BODY()

public:
    ATerrainManager();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

public:
    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunksX = 4;

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunksY = 4;

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunkWidth = 32;

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunkHeight = 32;

    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    float BlockSize = 100.f;

    UPROPERTY(EditAnywhere, Category = "Terrain|Settings")
    int32 Seed = 12345;

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    TSubclassOf<AChunkActor> ChunkClass;

    UPROPERTY(EditAnywhere, Category = "Terrain|Debug")
    bool bRegenerateNow = false;

    UPROPERTY(EditAnywhere, Category = "Terrain|Debug")
    bool bAutoRebuildInEditor = false;

private:
    UPROPERTY(Transient)
    TArray<AChunkActor*> SpawnedChunks;

    void ClearChunks();
    void BuildChunks();
};
