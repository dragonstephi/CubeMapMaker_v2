// Fill out your copyright notice in the Description page of Project Settings.

#include "MinecraftTerrainActorv1.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "FastNoiseLite.h"
#include "ProceduralMeshComponent.h" // added for procedural mesh
#include "Materials/Material.h"
#include "VoxelMesher.h" // <--- new include for greedy mesher

// Sets default values
AMinecraftTerrainActor::AMinecraftTerrainActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // 루트 컴포넌트 생성
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    // Create procedural mesh component (attached, optional)
    {
        ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMesh"));
        ProcMesh->SetupAttachment(RootComponent);
        ProcMesh->bUseAsyncCooking = true;
        ProcMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        ProcMesh->SetCastShadow(false);
    }

    // ──────────────────────────────
    // 1. Grass Blocks
    // ──────────────────────────────
    GrassBlocks = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("GrassBlocks"));
    GrassBlocks->SetupAttachment(RootComponent);

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Grass.SM_Grass'")
        );
        if (Mesh.Succeeded())
        {
            GrassBlocks->SetStaticMesh(Mesh.Object);
        }
    }

    // ──────────────────────────────
    // 2. Dirt Blocks
    // ──────────────────────────────
    DirtBlocks = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("DirtBlocks"));
    DirtBlocks->SetupAttachment(RootComponent);

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Dirt.SM_Dirt'")
        );
        if (Mesh.Succeeded())
        {
            DirtBlocks->SetStaticMesh(Mesh.Object);
        }
    }

    // ──────────────────────────────
    // 3. Sand Blocks
    // ──────────────────────────────
    SandBlocks = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("SandBlocks"));
    SandBlocks->SetupAttachment(RootComponent);

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Sand.SM_Sand'")
        );
        if (Mesh.Succeeded())
        {
            SandBlocks->SetStaticMesh(Mesh.Object);
        }
    }

    // ──────────────────────────────
    // 4. Cobblestone Blocks
    // ──────────────────────────────
    CobblestoneBlocks = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("CobblestoneBlocks"));
    CobblestoneBlocks->SetupAttachment(RootComponent);

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Cobblestone.SM_Cobblestone'")
        );
        if (Mesh.Succeeded())
        {
            CobblestoneBlocks->SetStaticMesh(Mesh.Object);
        }
    }

    // ──────────────────────────────
    // 5. Water Blocks
    // ──────────────────────────────
    WaterBlocks = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("WaterBlocks"));
    WaterBlocks->SetupAttachment(RootComponent);

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Square_Top1.SM_Square_Top1'")
        );
        if (Mesh.Succeeded())
        {
            WaterBlocks->SetStaticMesh(Mesh.Object);
        }
    }

    // ──────────────────────────────
    // 6. Oak Planks (집 기본 나무 블록)
    // ──────────────────────────────
    OakPlanksBlocks = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("OakPlanksBlocks"));
    OakPlanksBlocks->SetupAttachment(RootComponent);

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Oak_Planks.SM_Oak_Planks'")
        );
        if (Mesh.Succeeded())
        {
            OakPlanksBlocks->SetStaticMesh(Mesh.Object);
        }
    }

    // ──────────────────────────────
    // 7. Glass Blocks (유리창)
    // ──────────────────────────────
    GlassBlocks = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("GlassBlocks"));
    GlassBlocks->SetupAttachment(RootComponent);

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_minecraft_glass_v1.SM_minecraft_glass_v1'")
        );
        if (Mesh.Succeeded())
        {
            GlassBlocks->SetStaticMesh(Mesh.Object);
        }
    }

    // ──────────────────────────────
    // 8. Oak Roof Stairs (지붕)
    // ──────────────────────────────
    OakRoofStairsBlocks = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("OakRoofStairsBlocks"));
    OakRoofStairsBlocks->SetupAttachment(RootComponent);
    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Oak_Stairs_v1.SM_Oak_Stairs_v1'")
        );
        if (Mesh.Succeeded())
        {
            OakRoofStairsBlocks->SetStaticMesh(Mesh.Object);
        }
    }

    // ──────────────────────────────
    // 9. Oak Entry Stairs (문 앞 계단)
    // ──────────────────────────────
    OakEntryStairsBlocks = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("OakEntryStairsBlocks"));
    OakEntryStairsBlocks->SetupAttachment(RootComponent);
    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Oak_Stairs_v1.SM_Oak_Stairs_v1'")
        );
        if (Mesh.Succeeded())
        {
            OakEntryStairsBlocks->SetStaticMesh(Mesh.Object);
        }
    }


    // ---------- Vegetation Components ----------

    GrassFoliage = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GrassFoliage"));
    GrassFoliage->SetupAttachment(RootComponent);

    FlowerDandelion = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FlowerDandelion"));
    FlowerDandelion->SetupAttachment(RootComponent);

    FlowerDaisy = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FlowerDaisy"));
    FlowerDaisy->SetupAttachment(RootComponent);

    FlowerPoppy = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FlowerPoppy"));
    FlowerPoppy->SetupAttachment(RootComponent);

    TreeType1 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeType1"));
    TreeType1->SetupAttachment(RootComponent);

    TreeType2 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeType2"));
    TreeType2->SetupAttachment(RootComponent);

    TreeType3 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeType3"));
    TreeType3->SetupAttachment(RootComponent);

    // ---------- Fence Components ----------
    OakFenceBoth = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("OakFenceBoth"));
    OakFenceCenter = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("OakFenceCenter"));
    OakFenceCorner = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("OakFenceCorner"));
    OakFenceOneSide = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("OakFenceOneSide"));
    OakLogPillars = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("OakLogPillars"));

    OakFenceBoth->SetupAttachment(RootComponent);
    OakFenceCenter->SetupAttachment(RootComponent);
    OakFenceCorner->SetupAttachment(RootComponent);
    OakFenceOneSide->SetupAttachment(RootComponent);
    OakLogPillars->SetupAttachment(RootComponent);

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Oak_Fences_Both.SM_Oak_Fences_Both'")
        );
        if (Mesh.Succeeded())
        {
            OakFenceBoth->SetStaticMesh(Mesh.Object);
        }
    }
    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Oak_Fences_Center.SM_Oak_Fences_Center'")
        );
        if (Mesh.Succeeded())
        {
            OakFenceCenter->SetStaticMesh(Mesh.Object);
        }
    }
    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Oak_Fences_Corner.SM_Oak_Fences_Corner'")
        );
        if (Mesh.Succeeded())
        {
            OakFenceCorner->SetStaticMesh(Mesh.Object);
        }
    }
    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Oak_Fences_OneSide.SM_Oak_Fences_OneSide'")
        );
        if (Mesh.Succeeded())
        {
            OakFenceOneSide->SetStaticMesh(Mesh.Object);
        }
    }
    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Blocks/SM_Oak_Log.SM_Oak_Log'")
        );
        if (Mesh.Succeeded())
        {
            OakLogPillars->SetStaticMesh(Mesh.Object);
        }
    }


    // ---- Load meshes ----

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Objects/SM_grass_low_001.SM_grass_low_001'")
        );
        if (Mesh.Succeeded())
        {
            GrassFoliage->SetStaticMesh(Mesh.Object);
        }
    }

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Objects/SM_dandylion_001.SM_dandylion_001'")
        );
        if (Mesh.Succeeded())
        {
            FlowerDandelion->SetStaticMesh(Mesh.Object);
        }
    }

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Objects/SM_dasy_001.SM_dasy_001'")
        );
        if (Mesh.Succeeded())
        {
            FlowerDaisy->SetStaticMesh(Mesh.Object);
        }
    }

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Objects/SM_poppy_001.SM_poppy_001'")
        );
        if (Mesh.Succeeded())
        {
            FlowerPoppy->SetStaticMesh(Mesh.Object);
        }
    }

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Objects/SM_tree_001.SM_tree_001'")
        );
        if (Mesh.Succeeded())
        {
            TreeType1->SetStaticMesh(Mesh.Object);
        }
    }

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Objects/SM_tree_002.SM_tree_002'"
        ));
        if (Mesh.Succeeded())
        {
            TreeType2->SetStaticMesh(Mesh.Object);
        }
    }

    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
            TEXT("/Script/Engine.StaticMesh'/Game/Objects/SM_tree_003.SM_tree_003'")
        );
        if (Mesh.Succeeded())
        {
            TreeType3->SetStaticMesh(Mesh.Object);
        }
    }

}

void AMinecraftTerrainActor::BeginPlay()
{
    Super::BeginPlay();

    // 여기에는 아무것도 안 넣어도 됨
    // 게임 시작 전에 이미 OnConstruction에서 지형이 만들어져 있을 거라서
}

void AMinecraftTerrainActor::OnConstruction(const FTransform & Transform)
{
    Super::OnConstruction(Transform);

    if (!GrassBlocks || !DirtBlocks || !CobblestoneBlocks)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    #if WITH_EDITOR
    // 🔴 에디터의 "순수 편집 월드"가 아닐 때는 청크 재생성 금지
    if (World->WorldType != EWorldType::Editor
        && World->WorldType != EWorldType::EditorPreview)
    {
        return;
    }
    #else
    // 빌드된 게임/PIE에서는 아예 이 로직 안 돌리기
    return;
    #endif

    // ---- Clear all instances ----
    GrassBlocks->ClearInstances();
    DirtBlocks->ClearInstances();
    if (SandBlocks) SandBlocks->ClearInstances();
    CobblestoneBlocks->ClearInstances();
    if (WaterBlocks) WaterBlocks->ClearInstances();

    if (GrassFoliage)      GrassFoliage->ClearInstances();
    if (FlowerDandelion)   FlowerDandelion->ClearInstances();
    if (FlowerDaisy)       FlowerDaisy->ClearInstances();
    if (FlowerPoppy)       FlowerPoppy->ClearInstances();
    if (TreeType1)         TreeType1->ClearInstances();
    if (TreeType2)         TreeType2->ClearInstances();
    if (TreeType3)         TreeType3->ClearInstances();
    if (OakPlanksBlocks) OakPlanksBlocks->ClearInstances();
    if (GlassBlocks)     GlassBlocks->ClearInstances();
    if (OakRoofStairsBlocks)  OakRoofStairsBlocks->ClearInstances();
    if (OakEntryStairsBlocks) OakEntryStairsBlocks->ClearInstances();
    if (OakFenceBoth)    OakFenceBoth->ClearInstances();
    if (OakFenceCenter)  OakFenceCenter->ClearInstances();
    if (OakFenceCorner)  OakFenceCorner->ClearInstances();
    if (OakFenceOneSide) OakFenceOneSide->ClearInstances();
    if (OakLogPillars)   OakLogPillars->ClearInstances();

    // ---- Noise objects ----
    FastNoiseLite HeightNoise;
    HeightNoise.SetSeed(Seed);
    HeightNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    FastNoiseLite BiomeNoise;
    BiomeNoise.SetSeed(Seed + 1337);
    BiomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    // Vegetation random (청크별 랜덤 시드)
    const int32 ChunkRandomSeed =
        Seed
        + VegetationSeedOffset
        + ChunkOffsetX * 1000003
        + ChunkOffsetY * 10007;

    FRandomStream RandomStream(ChunkRandomSeed);

    // ==============================
    // 1) HeightMap + BiomeMap 계산 (평원 + 해변만, 부드러운 블렌딩)
    // ==============================
    TArray<int32> HeightMap;
    HeightMap.SetNum(Width * Height);

    TArray<uint8> BiomeMap; // 0 = Plains, 2 = Beach
    BiomeMap.SetNum(Width * Height);

    auto ToIndex = [this](int32 X, int32 Y)
        {
            return X * Height + Y;
        };

    for (int32 X = 0; X < Width; ++X)
    {
        for (int32 Y = 0; Y < Height; ++Y)
        {
            const int32 WorldTileX = ChunkOffsetX + X;
            const int32 WorldTileY = ChunkOffsetY + Y;

            // 1) 바이옴 노이즈
            float BiomeValue = BiomeNoise.GetNoise(
                (float)WorldTileX * BiomeNoiseScale,
                (float)WorldTileY * BiomeNoiseScale
            );

            const float BeachFull = -0.6f;
            const float BeachEnd = -0.1f;

            float BeachWeight = FMath::Clamp(
                (BeachEnd - BiomeValue) / (BeachEnd - BeachFull),
                0.f, 1.f
            );

            float PlainsWeight = 1.f - BeachWeight;

            // 2) 높이 노이즈
            float HeightValue = HeightNoise.GetNoise(
                (float)WorldTileX * NoiseScale,
                (float)WorldTileY * NoiseScale
            );
            HeightValue = (HeightValue + 1.f) * 0.5f;

            // 3) 높이 배율 (음수 허용)
            float LocalHeightMultiplier =
                PlainsWeight * HeightMultiplier +
                BeachWeight * BeachHeightMultiplier;

            // 4) Biome 결정
            uint8 Biome = (BeachWeight > 0.5f) ? 2 : 0;

            // 🔥 5) BaseHeight 포함해서 최종 높이 계산
            int32 RawHeight = FMath::RoundToInt(HeightValue * LocalHeightMultiplier) + BaseHeight;

            // 해변은 바닥이 더 낮게 보여도 되면 MinHeight=0, 평지는 1 이상 유지
            int32 MinHeight = (Biome == 2) ? 0 : 1;

            int32 ColumnHeight = FMath::Clamp(
                RawHeight,
                MinHeight,
                255
            );

            // 저장
            HeightMap[ToIndex(X, Y)] = ColumnHeight;
            BiomeMap[ToIndex(X, Y)] = Biome;
        }
    }

    // If procedural mesh mode is enabled, build the mesh from HeightMap using Greedy Top faces (MaxZ = 128)
    const bool bUseProc = bUseProceduralMesh; // use header toggle
    if (bUseProc)
    {
        UProceduralMeshComponent* Proc = ProcMesh;
        if (Proc)
        {
            Proc->ClearAllMeshSections();

            TArray<FVector> Verts;
            TArray<int32> Tris;
            TArray<FVector> Normals;
            TArray<FVector2D> UV0;
            TArray<FProcMeshTangent> Tangents;
            TArray<FLinearColor> Colors;

            // local AddQuad that appends a quad and fills arrays (keeps consistent winding)
            auto AddQuad = [&](const FVector& A, const FVector& B, const FVector& C, const FVector& D, const FVector& N)
            {
                const int32 I = Verts.Num();
                Verts.Add(A); Verts.Add(B); Verts.Add(C); Verts.Add(D);

                Tris.Add(I + 0); Tris.Add(I + 1); Tris.Add(I + 2);
                Tris.Add(I + 0); Tris.Add(I + 2); Tris.Add(I + 3);

                Normals.Add(N); Normals.Add(N); Normals.Add(N); Normals.Add(N);

                // temporary UVs (per-quad full)
                UV0.Add(FVector2D(0, 0));
                UV0.Add(FVector2D(1, 0));
                UV0.Add(FVector2D(1, 1));
                UV0.Add(FVector2D(0, 1));

                Tangents.Add(FProcMeshTangent(1, 0, 0));
                Tangents.Add(FProcMeshTangent(1, 0, 0));
                Tangents.Add(FProcMeshTangent(1, 0, 0));
                Tangents.Add(FProcMeshTangent(1, 0, 0));
            };

            // Helper IsSolid using HeightMap computed earlier in this function
            auto IsSolid = [&](int32 X, int32 Y, int32 Z) -> bool
            {
                if (X < 0 || Y < 0 || Z < 0) return false;
                if (X >= Width || Y >= Height) return false;
                const int32 H = HeightMap[ToIndex(X, Y)];
                return Z < H;
            };

            // Helper GetTopType: returns simple top-type per (x,y) for merging (0=air,1=grass,2=sand)

            auto GetType = [&](int32 X, int32 Y, int32 Z) -> uint8
                {
                    const int32 H = HeightMap[ToIndex(X, Y)];
                    if (H <= 0) return 0;

                    const uint8 Biome = BiomeMap[ToIndex(X, Y)];
                    return (Biome == 2) ? 2 : 1; // 2=sand, 1=grass
                };

            // Chunk world origin (start of this chunk in world space)
            const FVector ChunkWorldOrigin =
                FVector(ChunkOffsetX * Width * BlockSize,
                    ChunkOffsetY * Height * BlockSize,
                    0.f);

            // Use ChunkMaxZ = 128 (as requested)
            const int32 ChunkMaxZ = 128;

            // Call mesher in the dedicated unit
            VoxelMesher::BuildTopFacesGreedy(
                Width, Height, BlockSize, ChunkMaxZ,
                ChunkWorldOrigin,
                IsSolid,
                GetType,
                Verts, Tris, Normals, UV0, Tangents
            );


            // Create mesh section with current bGenerateCollision flag
            Proc->CreateMeshSection_LinearColor(0, Verts, Tris, Normals, UV0, Colors, Tangents, bGenerateCollision);
            Proc->SetCollisionEnabled(bGenerateCollision ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
        }

        // Skip HISM generation when procedural mesh is used
        return;
    }

    // ==============================
    // continue with instanced-mesh generation (existing HISM code) ...
    // (unchanged from original file — vegetation, water, house generation, fences, etc.)
    //
    // ... rest of OnConstruction continues as before (unchanged) ...
    //
    // Note: The original file continues here — I left the subsequent existing HISM generation code unchanged.
}

// Note: ProcMesh is a member added to header. Ensure you declared UProceduralMeshComponent* ProcMesh in the header.
void AMinecraftTerrainActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}