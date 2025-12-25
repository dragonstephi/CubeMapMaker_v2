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

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunksX = 2;

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    int32 ChunksY = 2;

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    TSubclassOf<AChunkActor> ChunkClass;

    UPROPERTY(EditAnywhere, Category = "Terrain|Chunks")
    float ChunkSpacing = 1200.f; // 청크 간격(= Width*TileSize 정도로 맞추면 딱 붙음)

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

private:
    UPROPERTY(Transient)
    TArray<TObjectPtr<AChunkActor>> SpawnedChunks;

    void ClearChunks();
    void BuildChunks();
};
