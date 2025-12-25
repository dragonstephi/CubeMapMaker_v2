#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkActor.generated.h"

class UProceduralMeshComponent;

UCLASS()
class CUBEMAPMAKER_V2_API AChunkActor : public AActor
{
    GENERATED_BODY()

public:
    AChunkActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chunk")
    UProceduralMeshComponent* ProcMesh;

    UPROPERTY(EditAnywhere, Category = "Chunk")
    int32 SizeX = 32;

    UPROPERTY(EditAnywhere, Category = "Chunk")
    int32 SizeY = 32;

    UPROPERTY(EditAnywhere, Category = "Chunk")
    float BlockSize = 100.f;

    UFUNCTION(CallInEditor, Category = "Chunk")
    void RebuildChunk();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

private:
    void BuildFlatMesh();
};
