#include "ChunkActor.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

AChunkActor::AChunkActor()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMesh"));
    ProcMesh->SetupAttachment(RootComponent);
    ProcMesh->SetMobility(EComponentMobility::Movable);
    ProcMesh->bUseAsyncCooking = true;
}

void AChunkActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    BuildFlatMesh();
}

void AChunkActor::RebuildChunk()
{
    BuildFlatMesh();
}

void AChunkActor::BuildFlatMesh()
{
    if (!ProcMesh) return;

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UV0;
    TArray<FProcMeshTangent> Tangents;
    TArray<FLinearColor> Colors;

    const float W = SizeX * BlockSize;
    const float H = SizeY * BlockSize;

    Vertices = {
        FVector(0,   0,   0),
        FVector(W,   0,   0),
        FVector(W,   H,   0),
        FVector(0,   H,   0),
    };

    Triangles = { 0,1,2, 0,2,3 };

    UV0 = {
        FVector2D(0,0),
        FVector2D(1,0),
        FVector2D(1,1),
        FVector2D(0,1),
    };

    // Tangent/Normal 계산
    TArray<FVector> TempNormals;
    TArray<FProcMeshTangent> TempTangents;
    UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, TempNormals, TempTangents);
    Normals = TempNormals;
    Tangents = TempTangents;

    Colors.Init(FLinearColor::White, Vertices.Num());

    ProcMesh->ClearAllMeshSections();
    ProcMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, Colors, Tangents, true);

    UE_LOG(LogTemp, Warning, TEXT("[Chunk] V=%d T=%d"), Vertices.Num(), Triangles.Num());
}
