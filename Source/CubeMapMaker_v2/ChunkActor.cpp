// ChunkActor.cpp
#include "ChunkActor.h"
#include "ProceduralMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetProceduralMeshLibrary.h"

AChunkActor::AChunkActor()
{
    PrimaryActorTick.bCanEverTick = false;

    ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMesh"));
    SetRootComponent(ProcMesh);
    ProcMesh->bUseAsyncCooking = true;
}

void AChunkActor::BuildChunk(int32 InWidth, int32 InHeight, float InBlockSize, int32 InSeed, FIntPoint InChunkCoord)
{
    Width = InWidth;
    Height = InHeight;
    BlockSize = InBlockSize;
    Seed = InSeed;
    ChunkCoord = InChunkCoord;

    GenerateSimpleSurfaceMesh();
    bBuiltOnce = true;

    if (Material)
    {
        ProcMesh->SetMaterial(0, Material);
    }
}

void AChunkActor::Rebuild()
{
    if (!bBuiltOnce)
        return;

    GenerateSimpleSurfaceMesh();

    if (Material)
    {
        ProcMesh->SetMaterial(0, Material);
    }
}

void AChunkActor::GenerateSimpleSurfaceMesh()
{
    ProcMesh->ClearAllMeshSections();

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UV0;
    TArray<FProcMeshTangent> Tangents;
    TArray<FLinearColor> Colors;

    Vertices.Reserve((Width + 1) * (Height + 1));
    UV0.Reserve((Width + 1) * (Height + 1));

    auto GetHeight = [&](int32 X, int32 Y) -> float
        {
            // “청크 경계 이어짐”을 위해 월드 좌표 기반으로 노이즈 샘플
            const float WorldX = (ChunkCoord.X * Width + X) * 0.08f;
            const float WorldY = (ChunkCoord.Y * Height + Y) * 0.08f;

            // Seed로 약간 흔들기(가벼운 방식)
            const float S = (float)Seed * 0.001f;
            const float N = FMath::PerlinNoise2D(FVector2D(WorldX + S, WorldY + S));
            return N * 800.f; // 높이 스케일(나중에 파라미터화)
        };

    // 정점 생성
    for (int32 y = 0; y <= Height; y++)
    {
        for (int32 x = 0; x <= Width; x++)
        {
            const float H = GetHeight(x, y);
            Vertices.Add(FVector(x * BlockSize, y * BlockSize, H));
            UV0.Add(FVector2D((float)x / (float)Width, (float)y / (float)Height));
            Colors.Add(FLinearColor::White);
        }
    }

    auto Idx = [&](int32 x, int32 y) -> int32
        {
            return y * (Width + 1) + x;
        };

    // 삼각형 인덱스
    for (int32 y = 0; y < Height; y++)
    {
        for (int32 x = 0; x < Width; x++)
        {
            const int32 i0 = Idx(x, y);
            const int32 i1 = Idx(x + 1, y);
            const int32 i2 = Idx(x, y + 1);
            const int32 i3 = Idx(x + 1, y + 1);

            // (i0, i2, i1), (i1, i2, i3)
            Triangles.Add(i0);
            Triangles.Add(i2);
            Triangles.Add(i1);

            Triangles.Add(i1);
            Triangles.Add(i2);
            Triangles.Add(i3);
        }
    }

    // 노멀 간단 계산 (UE 헬퍼)
    Normals.SetNumZeroed(Vertices.Num());
    Tangents.SetNumZeroed(Vertices.Num());
    TArray<FVector> TempNormals;
    TArray<FProcMeshTangent> TempTangents;
    UKismetProceduralMeshLibrary::CalculateTangentsForMesh(
        Vertices,
        Triangles,
        UV0,
        TempNormals,
        TempTangents
    );
    Normals = MoveTemp(TempNormals);
    Tangents = MoveTemp(TempTangents);

    ProcMesh->CreateMeshSection_LinearColor(
        0,
        Vertices,
        Triangles,
        Normals,
        UV0,
        Colors,
        Tangents,
        true // collision
    );

    UE_LOG(LogTemp, Warning, TEXT("[ChunkActor] Built. V=%d T=%d (%d tris)"), Vertices.Num(), Triangles.Num(), Triangles.Num() / 3);
}
