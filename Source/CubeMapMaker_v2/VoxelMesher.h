#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"

// 그냥 유틸 함수 선언만 둔다 (UCLASS/GENERATED_BODY 절대 없음)
namespace VoxelMesher
{
    // AddQuad 헬퍼 (ProcMesh용)
    void AddQuad(
        TArray<FVector>& Verts,
        TArray<int32>& Tris,
        TArray<FVector>& Normals,
        TArray<FVector2D>& UV0,
        TArray<FProcMeshTangent>& Tangents,
        const FVector& A, const FVector& B, const FVector& C, const FVector& D,
        const FVector& N
    );

    // Top-face Greedy
    void BuildTopFacesGreedy(
        int32 Width, int32 Height, float BlockSize, int32 ChunkMaxZ,
        const FVector& ChunkWorldOrigin,
        TFunctionRef<bool(int32, int32, int32)> IsSolid,     // (x,y,z)
        TFunctionRef<uint8(int32, int32, int32)> GetType,    // (x,y,z) block type
        TArray<FVector>& Verts,
        TArray<int32>& Tris,
        TArray<FVector>& Normals,
        TArray<FVector2D>& UV0,
        TArray<FProcMeshTangent>& Tangents
    );
}
