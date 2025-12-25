// ChunkActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkActor.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class CUBEMAPMAKER_V2_API AChunkActor : public AActor
{
    GENERATED_BODY()

public:
    AChunkActor();

    // 청크 빌드(Manager가 호출)
    void BuildChunk(int32 InWidth, int32 InHeight, float InBlockSize, int32 InSeed, FIntPoint InChunkCoord);

    // 디버그용 재생성
    UFUNCTION(CallInEditor, Category = "Chunk")
    void Rebuild();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UProceduralMeshComponent* ProcMesh;

    // 청크 메쉬 머티리얼 (단일 머티리얼로 시작)
    UPROPERTY(EditAnywhere, Category = "Chunk|Render")
    UMaterialInterface* Material = nullptr;

    UPROPERTY(EditAnywhere, Category = "Chunk|Settings")
    int32 Width = 32;

    UPROPERTY(EditAnywhere, Category = "Chunk|Settings")
    int32 Height = 32;

    UPROPERTY(EditAnywhere, Category = "Chunk|Settings")
    float BlockSize = 100.f;

    UPROPERTY(EditAnywhere, Category = "Chunk|Settings")
    int32 Seed = 12345;

    UPROPERTY(VisibleAnywhere, Category = "Chunk|Settings")
    FIntPoint ChunkCoord = FIntPoint::ZeroValue;

private:
    // 아주 단순한 “높이맵 기반 표면 메쉬” (최소 버전)
    void GenerateSimpleSurfaceMesh();

    // 내부 캐시
    bool bBuiltOnce = false;
};
