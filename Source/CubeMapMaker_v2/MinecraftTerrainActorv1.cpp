// Fill out your copyright notice in the Description page of Project Settings.

#include "MinecraftTerrainActorv1.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "FastNoiseLite.h"

    // Sets default values
    AMinecraftTerrainActor::AMinecraftTerrainActor()
    {
        PrimaryActorTick.bCanEverTick = false;

        // 루트 컴포넌트 생성
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

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

        // ============= 여기까지 준비, 아래에서 실제 벽/창문 루프에서 사용 =============


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

        // 이웃 칸 높이 얻기 (맵 밖은 -1 = 공기)
        auto GetHeight = [&HeightMap, this, &ToIndex](int32 X, int32 Y) -> int32
            {
                if (X < 0 || X >= Width || Y < 0 || Y >= Height)
                {
                    return -1;
                }
                return HeightMap[ToIndex(X, Y)];
            };

        auto CountWaterNeighbors = [&](int32 X, int32 Y) -> int32
            {
                int32 Count = 0;
                const int32 L = GetHeight(X - 1, Y);
                const int32 R = GetHeight(X + 1, Y);
                const int32 B = GetHeight(X, Y - 1);
                const int32 F = GetHeight(X, Y + 1);

                const int32 Threshold = SeaLevelBlocks; // 필요하면 SeaLevelBlocks-1 로 바꿔봐도 됨

                if (L >= Threshold) ++Count;
                if (R >= Threshold) ++Count;
                if (B >= Threshold) ++Count;
                if (F >= Threshold) ++Count;

                return Count;
            };

        // ==============================
        // 1.5) 집 청크일 경우, HeightMap 기반으로 지형 평탄화 + HouseNoVegArea 설정
        // ==============================
        if (bGenerateSampleHouse)
        {
            // 1) 집 크기 보정
            const int32 UseSizeX = FMath::Clamp(HouseSizeX, 3, Width);
            const int32 UseSizeY = FMath::Clamp(HouseSizeY, 3, Height);

            // 2) 청크 중앙 + 오프셋
            int32 CenterX = Width / 2 + HouseCenterOffsetX;
            int32 CenterY = Height / 2 + HouseCenterOffsetY;

            CenterX = FMath::Clamp(CenterX, 0, Width - 1);
            CenterY = FMath::Clamp(CenterY, 0, Height - 1);

            const int32 HalfX = UseSizeX / 2;
            const int32 HalfY = UseSizeY / 2;

            int32 StartX = FMath::Clamp(CenterX - HalfX, 0, Width - 1);
            int32 EndX = FMath::Clamp(CenterX + HalfX, 0, Width - 1);
            int32 StartY = FMath::Clamp(CenterY - HalfY, 0, Height - 1);
            int32 EndY = FMath::Clamp(CenterY + HalfY, 0, Height - 1);

            // 3) 중앙 타일 높이 기준 평탄화 높이 결정
            const int32 CenterIndex = ToIndex(CenterX, CenterY);
            int32 PlateauHeight = HeightMap[CenterIndex];
            PlateauHeight = FMath::Max(PlateauHeight, 1);

            // 🔥 4) 집 주변을 넉넉하게 평탄화
            //    - 집 영역 + HouseFlattenMargin 만큼을 "완전 플랫"
            //    - 이렇게 하면 집 크기가 커져도, 노이즈가 세도 지형이 집을 뚫지 않음
            const int32 FlatMargin = FMath::Max(HouseFlattenMargin, 1);

            const int32 FlatStartX = FMath::Clamp(StartX - FlatMargin, 0, Width - 1);
            const int32 FlatEndX = FMath::Clamp(EndX + FlatMargin, 0, Width - 1);
            const int32 FlatStartY = FMath::Clamp(StartY - FlatMargin, 0, Height - 1);
            const int32 FlatEndY = FMath::Clamp(EndY + FlatMargin, 0, Height - 1);

            for (int32 HX = FlatStartX; HX <= FlatEndX; ++HX)
            {
                for (int32 HY = FlatStartY; HY <= FlatEndY; ++HY)
                {
                    const int32 Idx = ToIndex(HX, HY);
                    int32& H = HeightMap[Idx];

                    // 여기는 완전히 PlateauHeight 로 "고정"
                    // → 높은 언덕도 깎아내리고, 낮은 부분도 올려버림
                    H = PlateauHeight;
                }
            }

            // 5) HouseNoVegArea 설정 (집 + 마당 영역 식생 금지)
            HouseNoVegArea.Empty();

            // 평탄화 영역보다 살짝 더 크게 마당을 잡고 싶으면 +1 정도 더
            const int32 VegMargin = FlatMargin + 1;

            const int32 VegStartX = FMath::Clamp(StartX - VegMargin, 0, Width - 1);
            const int32 VegEndX = FMath::Clamp(EndX + VegMargin, 0, Width - 1);
            const int32 VegStartY = FMath::Clamp(StartY - VegMargin, 0, Height - 1);
            const int32 VegEndY = FMath::Clamp(EndY + VegMargin, 0, Height - 1);

            for (int32 HX = VegStartX; HX <= VegEndX; ++HX)
            {
                for (int32 HY = VegStartY; HY <= VegEndY; ++HY)
                {
                    HouseNoVegArea.Add(FIntPoint(HX, HY));
                }
            }

            // 6) 나중에 집 생성 파트에서 사용할 값들 저장
            HouseStartX = StartX;
            HouseEndX = EndX;
            HouseStartY = StartY;
            HouseEndY = EndY;
            HouseFloorHeightBlocks = PlateauHeight; // 집 바닥 높이(블록 단위)
        }

        // ==============================
        // 2) Visible Blocks만 생성 + 같은 루프에서 식생 판단까지
        // ==============================
        for (int32 X = 0; X < Width; ++X)
        {
            for (int32 Y = 0; Y < Height; ++Y)
            {
                const int32 Index = ToIndex(X, Y);
                const int32 ColumnHeight = HeightMap[Index];
                const uint8 Biome = BiomeMap[Index];

                if (ColumnHeight <= 0)
                {
                    continue;
                }

                int32 MinHeight = (Biome == 2) ? 0 : 1; // beach=0, plain=1

                // 이웃 칸 높이
                const int32 LeftHeight = GetHeight(X - 1, Y);
                const int32 RightHeight = GetHeight(X + 1, Y);
                const int32 BackHeight = GetHeight(X, Y - 1);
                const int32 FrontHeight = GetHeight(X, Y + 1);

                for (int32 Z = 0; Z < ColumnHeight; ++Z)
                {
                    bool bVisible = false;

                    // 1) 맨 위 블록은 무조건 보임 (위가 공기)
                    if (Z == ColumnHeight - 1)
                    {
                        bVisible = true;
                    }
                    else
                    {
                        // 2) 옆면이 공기와 맞닿는 경우 (절벽/경사면)
                        if (Z >= LeftHeight ||
                            Z >= RightHeight ||
                            Z >= BackHeight ||
                            Z >= FrontHeight)
                        {
                            bVisible = true;
                        }
                    }

                    if (!bVisible)
                    {
                        // 완전히 내부에 묻힌 블록 → 생성 안 함
                        continue;
                    }

                    FVector BlockLocation(
                        X * BlockSize,
                        Y * BlockSize,
                        Z * BlockSize
                    );

                    FTransform BlockTransform(
                        FRotator::ZeroRotator,
                        BlockLocation,
                        FVector(1.f)
                    );

                    // 🔹 Biome 별 블록 팔레트
                    if (Biome == 2) // Beach / 사막 / 해변
                    {
                        // 가장 윗층은 Sand
                        if (Z == ColumnHeight - 1)
                        {
                            if (SandBlocks)
                            {
                                SandBlocks->AddInstance(BlockTransform);
                            }
                            else
                            {
                                GrassBlocks->AddInstance(BlockTransform);
                            }
                        }
                        // 그 아래는 돌(해변 암석층)
                        else if (Z >= ColumnHeight - 3)
                        {
                            CobblestoneBlocks->AddInstance(BlockTransform);
                        }
                        else
                        {
                            CobblestoneBlocks->AddInstance(BlockTransform);
                        }
                    }
                    else // Plains
                    {
                        // 평원: 맨 위는 Grass
                        if (Z == ColumnHeight - 1)
                        {
                            GrassBlocks->AddInstance(BlockTransform);
                        }
                        else
                        {
                            CobblestoneBlocks->AddInstance(BlockTransform);
                        }
                    }
                }


                // ======================
                // 3) Vegetation 스폰 (타일당 최대 1개, 물 타일에는 심지 않기)
                // ======================
                const float GroundTopZ = (ColumnHeight - 1) * BlockSize + BlockSize * 0.5f;
                bool bWaterCandidate = false;

                // 해변 + 수면보다 낮은 타일만 물 후보
                if (Biome == 2 && ColumnHeight < SeaLevelBlocks)
                {
                    if (bWaterSimpleMode)
                    {
                        // 🔹 단순 모드: 이웃 검사 안 하고 해변 저지대는 전부 물 후보
                        bWaterCandidate = true;
                    }
                    else
                    {
                        // 🔹 고급 모드: 이웃 개수 기준으로 웅덩이만 물 후보
                        const int32 NeighborHighCount = CountWaterNeighbors(X, Y);

                        // 에디터에서 WaterNeighborRequired 로 최소 이웃 수 조절
                        bWaterCandidate = (NeighborHighCount >= WaterNeighborRequired);
                    }
                }

                // 물이 들어갈 타일이면 식생 스킵
                if (bWaterCandidate)
                {
                    continue;
                }

                // 집 내부/바로 주변(기본) 식생 금지
                if (HouseNoVegArea.Contains(FIntPoint(X, Y)))
                {
                    // 이 타일은 집/마당이니 식생 스킵
                    continue;
                }

                // 🌲 나무만 집 주변 조금 더 넉넉하게 비우고 싶을 때:
                auto IsNearHouseForTree = [&](int32 TX, int32 TY) -> bool
                    {
                        // 반경 1칸(3x3)을 스캔. 더 넓게 하고 싶으면 2로 바꾸면 됨.
                        for (int32 dx = -1; dx <= 1; ++dx)
                        {
                            for (int32 dy = -1; dy <= 1; ++dy)
                            {
                                FIntPoint P(TX + dx, TY + dy);
                                if (HouseNoVegArea.Contains(P))
                                {
                                    return true;
                                }
                            }
                        }
                        return false;
                    };

                // 타일 중앙 위치
                FVector VegLocation(
                    X * BlockSize,
                    Y * BlockSize,
                    GroundTopZ
                );

                // 회전: 0 / 90 / 180 / 270
                int32 RotIndex = RandomStream.RandRange(0, 3);
                float Yaw = RotIndex * 90.f;
                FRotator VegRotator(0.f, Yaw, 0.f);
                FTransform VegTransform(VegRotator, VegLocation, FVector(1.f));

                // 누적 확률 (★ 여기서 한 번만 선언)
                const float TreeThreshold = TreeDensity;
                const float FlowerThreshold = TreeThreshold + FlowerDensity;
                const float GrassThreshold = FlowerThreshold + GrassDensity;

                const float Roll = RandomStream.FRand();

                // 1) 나무
                if (Roll < TreeThreshold)
                {
                    // 집 인근(반경 1칸)에는 나무 스킵
                    if (!IsNearHouseForTree(X, Y))
                    {
                        const int32 TreeType = RandomStream.RandRange(0, 2);
                        switch (TreeType)
                        {
                        case 0:
                            if (TreeType1) TreeType1->AddInstance(VegTransform);
                            break;
                        case 1:
                            if (TreeType2) TreeType2->AddInstance(VegTransform);
                            break;
                        case 2:
                            if (TreeType3) TreeType3->AddInstance(VegTransform);
                            break;
                        default:
                            break;
                        }
                    }
                }
                // 2) 꽃
                else if (Roll < FlowerThreshold)
                {
                    const int32 FlowerType = RandomStream.RandRange(0, 2);
                    switch (FlowerType)
                    {
                    case 0:
                        if (FlowerDandelion) FlowerDandelion->AddInstance(VegTransform);
                        break;
                    case 1:
                        if (FlowerDaisy) FlowerDaisy->AddInstance(VegTransform);
                        break;
                    case 2:
                        if (FlowerPoppy) FlowerPoppy->AddInstance(VegTransform);
                        break;
                    default:
                        break;
                    }
                }
                // 3) 풀
                else if (Roll < GrassThreshold)
                {
                    if (GrassFoliage)
                    {
                        GrassFoliage->AddInstance(VegTransform);
                    }
                }
                // 4) 그 외: 아무 것도 안 심음
            }
        }

        // ==============================
        // 4) Water 표면 생성 (해변 바이옴 & 주변이 더 높은 타일만)
        // ==============================
        if (WaterBlocks && SeaLevelBlocks > 0)
        {
            const float WaterZ = SeaLevelBlocks * BlockSize - 1.0f; // 필요하면 +1.f 정도 띄워도 됨

            for (int32 WX = 0; WX < Width; ++WX)
            {
                for (int32 WY = 0; WY < Height; ++WY)
                {
                    const int32 WIndex = ToIndex(WX, WY);
                    const int32 WColumnHeight = HeightMap[WIndex];
                    const uint8 WBiome = BiomeMap[WIndex];

                    // 해변 바이옴만
                    // 해변 바이옴만
                    if (WBiome != 2)
                    {
                        continue;
                    }

                    // 수면보다 높은 땅에는 물 없음
                    if (WColumnHeight >= SeaLevelBlocks)
                    {
                        continue;
                    }

                    bool bPlaceWater = false;

                    if (bWaterSimpleMode)
                    {
                        // 🔹 단순 모드: 해변 + 수면보다 낮은 칸이면 다 물
                        bPlaceWater = true;
                    }
                    else
                    {
                        // 🔹 고급 모드: 이웃 개수 기준
                        const int32 NeighborHighCount2 = CountWaterNeighbors(WX, WY);
                        bPlaceWater = (NeighborHighCount2 >= WaterNeighborRequired);
                    }

                    if (!bPlaceWater)
                    {
                        continue;
                    }

                    FVector WaterLocation(
                        WX * BlockSize,
                        WY * BlockSize,
                        WaterZ
                    );

                    FTransform WaterTransform(
                        FRotator::ZeroRotator,
                        WaterLocation,
                        FVector(1.f)
                    );

                    WaterBlocks->AddInstance(WaterTransform);
                }
            }
        }
        // ==============================
    // 5) Sample House / Restaurant 생성
        if (bGenerateSampleHouse && OakPlanksBlocks && GlassBlocks && OakRoofStairsBlocks && OakEntryStairsBlocks)
        {
            // ────────────────────────────────
            // 1) 집 크기 보정
            // ────────────────────────────────
            const int32 UseSizeX = FMath::Clamp(HouseSizeX, 3, Width);
            const int32 UseSizeY = FMath::Clamp(HouseSizeY, 3, Height);

            // 청크 중앙 + 오프셋
            int32 CenterX = FMath::Clamp(Width / 2 + HouseCenterOffsetX, 0, Width - 1);
            int32 CenterY = FMath::Clamp(Height / 2 + HouseCenterOffsetY, 0, Height - 1);

            const int32 HalfX = UseSizeX / 2;
            const int32 HalfY = UseSizeY / 2;

            int32 StartX = FMath::Clamp(CenterX - HalfX, 0, Width - 1);
            int32 EndX = FMath::Clamp(CenterX + HalfX, 0, Width - 1);
            int32 StartY = FMath::Clamp(CenterY - HalfY, 0, Height - 1);
            int32 EndY = FMath::Clamp(CenterY + HalfY, 0, Height - 1);

            // ────────────────────────────────
            // 2) 집 바닥 높이 (중앙지점 기준)
            // ────────────────────────────────
            const int32 CenterIndex = ToIndex(CenterX, CenterY);
            const int32 CenterColumnHeight = HeightMap[CenterIndex];
            if (CenterColumnHeight <= 0)
                return;

            const float GroundTopZ = (CenterColumnHeight - 1) * BlockSize + BlockSize * 0.5f;
            const float FloorZ = GroundTopZ; // 집 바닥을 지면 위에 딱 붙이기

            // ────────────────────────────────
            // 3) 문 위치 (앞벽: StartY 라인)
            // ────────────────────────────────
            const int32 DoorX = CenterX;
            const int32 DoorY = StartY;
            const int32 DoorHeightBlocks = 2;

            // ────────────────────────────────
            // 4) 집 주변 Vegetation 제거 범위 기록 (1칸 여유)
            // ────────────────────────────────
            HouseNoVegArea.Empty();
            const int32 Margin = 2;

            for (int32 HX = StartX - Margin; HX <= EndX + Margin; ++HX)
            {
                for (int32 HY = StartY - Margin; HY <= EndY + Margin; ++HY)
                {
                    if (HX >= 0 && HX < Width && HY >= 0 && HY < Height)
                    {
                        HouseNoVegArea.Add(FIntPoint(HX, HY));
                    }
                }
            }

            // ────────────────────────────────
            // 5) 바닥 + 벽 + 창문 생성
            // ────────────────────────────────
            
            // 5-0) 집 바닥 (나무 바닥) 생성
            {
                for (int32 HX = StartX; HX <= EndX; ++HX)
                {
                    for (int32 HY = StartY; HY <= EndY; ++HY)
                    {
                        FVector FloorLocation(
                            HX * BlockSize,
                            HY * BlockSize,
                            FloorZ   // 위에서 계산한 집 바닥 높이
                        );

                        OakPlanksBlocks->AddInstance(
                            FTransform(
                                FRotator::ZeroRotator,
                                FloorLocation,
                                FVector(1.f)
                            )
                        );
                    }
                }
            }


            // ============= 창문 배치 설정 + 계산 =============

            // (1) 창문 위치 계산 헬퍼 (가로)
            auto ComputeWindowRange = [](int32 Start, int32 End, int32 Center, int32 Count, int32 CenterOffset, TArray<int32>& OutIndices)
                {
                    OutIndices.Reset();

                    if (Count <= 0)
                    {
                        return;
                    }

                    int32 EffectiveCenter = Center + CenterOffset;
                    EffectiveCenter = FMath::Clamp(EffectiveCenter, Start, End);

                    const float Half = (Count - 1) * 0.5f;

                    for (int32 i = 0; i < Count; ++i)
                    {
                        const float OffsetF = (float)i - Half;
                        int32 Index = EffectiveCenter + FMath::RoundToInt(OffsetF);

                        Index = FMath::Clamp(Index, Start, End);
                        OutIndices.AddUnique(Index);
                    }
                };

            // (2) 창문 높이(층) 판정 – 벽별 VerticalOffset 적용
            auto IsWindowHeightForWall = [this](int32 HZ, int32 VerticalOffsetBlocks, int32 RowCountOverride) -> bool
                {
                    // RowCountOverride > 0 이면 그 값 우선, 아니면 공통 WindowRowCount 사용
                    int32 UseRowCount = (RowCountOverride > 0) ? RowCountOverride : WindowRowCount;

                    if (UseRowCount <= 0)
                    {
                        return false;
                    }

                    for (int32 Row = 0; Row < UseRowCount; ++Row)
                    {
                        const int32 RowZ =
                            FirstWindowHeightBlock
                            + VerticalOffsetBlocks
                            + Row * WindowRowSpacingBlocks;

                        if (RowZ < 1 || RowZ > this->HouseWallHeight)
                        {
                            continue;
                        }

                        if (HZ == RowZ)
                        {
                            return true;
                        }
                    }
                    return false;
                };


            // (3) 각 벽에 창문이 들어갈 인덱스 계산
            TArray<int32> FrontWindowXs;
            TArray<int32> BackWindowXs;
            TArray<int32> LeftWindowYs;
            TArray<int32> RightWindowYs;

            // ⬇⬇⬇ 여기서부터는 “로컬 const” 절대 선언하지 말고, 전부 멤버를 그대로 사용 ⬇⬇⬇
            ComputeWindowRange(StartX, EndX, CenterX, FrontWindowCount, FrontWindowCenterOffset, FrontWindowXs);
            ComputeWindowRange(StartX, EndX, CenterX, BackWindowCount, BackWindowCenterOffset, BackWindowXs);
            ComputeWindowRange(StartY, EndY, CenterY, LeftWindowCount, LeftWindowCenterOffset, LeftWindowYs);
            ComputeWindowRange(StartY, EndY, CenterY, RightWindowCount, RightWindowCenterOffset, RightWindowYs);


            for (int32 HX = StartX; HX <= EndX; ++HX)
            {
                for (int32 HY = StartY; HY <= EndY; ++HY)
                {
                    const bool bIsBorder = (HX == StartX || HX == EndX || HY == StartY || HY == EndY);
                    if (!bIsBorder)
                    {
                        continue;
                    }

                    const bool bIsFront = (HY == StartY);
                    const bool bIsBack = (HY == EndY);
                    const bool bIsLeft = (HX == StartX);
                    const bool bIsRight = (HX == EndX);

                    for (int32 HZ = 1; HZ <= HouseWallHeight; ++HZ)
                    {
                        // 문 위치
                        const bool bIsDoor =
                            bIsFront &&
                            HX == DoorX &&
                            HZ <= DoorHeightBlocks;

                        if (bIsDoor)
                        {
                            continue;
                        }

                        // 벽별 “이 높이가 창문층인가?” 판정
                        const bool bFrontHeight = bIsFront && IsWindowHeightForWall(HZ, FrontWindowVerticalOffsetBlocks, FrontWindowRowCountOverride);
                        const bool bBackHeight = bIsBack && IsWindowHeightForWall(HZ, BackWindowVerticalOffsetBlocks, BackWindowRowCountOverride);
                        const bool bLeftHeight = bIsLeft && IsWindowHeightForWall(HZ, LeftWindowVerticalOffsetBlocks, LeftWindowRowCountOverride);
                        const bool bRightHeight = bIsRight && IsWindowHeightForWall(HZ, RightWindowVerticalOffsetBlocks, RightWindowRowCountOverride);


                        // 문 양옆 창 제한 (front 전용)
                        bool bNearDoor = false;
                        if (bFrontHeight && !bAllowFrontWindowsNearDoor)
                        {
                            bNearDoor =
                                FMath::Abs(HX - DoorX) == 1;   // 같은 HZ에서만 처리하고 싶으면 && HZ == ... 추가 가능
                        }

                        bool bIsWindow = false;

                        if (!bNearDoor)
                        {
                            if (bFrontHeight && FrontWindowXs.Contains(HX))
                                bIsWindow = true;

                            if (bBackHeight && BackWindowXs.Contains(HX))
                                bIsWindow = true;

                            if (bLeftHeight && LeftWindowYs.Contains(HY))
                                bIsWindow = true;

                            if (bRightHeight && RightWindowYs.Contains(HY))
                                bIsWindow = true;
                        }

                        const float WallZ = FloorZ + HZ * BlockSize;
                        const FVector WallLocation(
                            HX * BlockSize,
                            HY * BlockSize,
                            WallZ
                        );

                        if (bIsWindow)
                        {
                            GlassBlocks->AddInstance(
                                FTransform(FRotator::ZeroRotator, WallLocation, FVector(1.f))
                            );
                        }
                        else
                        {
                            OakPlanksBlocks->AddInstance(
                                FTransform(FRotator::ZeroRotator, WallLocation, FVector(1.f))
                            );
                        }
                    }
                }
            }

            // ────────────────────────────────
            // 6) 천장 (벽 안쪽만)
            // ────────────────────────────────
            const float CeilingZ = FloorZ + (HouseWallHeight + 1) * BlockSize;

            for (int32 HX = StartX + 1; HX <= EndX - 1; ++HX)
            {
                for (int32 HY = StartY + 1; HY <= EndY - 1; ++HY)
                {
                    FVector CeilingLocation(
                        HX * BlockSize,
                        HY * BlockSize,
                        CeilingZ
                    );
                    OakPlanksBlocks->AddInstance(
                        FTransform(FRotator::ZeroRotator, CeilingLocation, FVector(1.f))
                    );
                }
            }

            // ==============================
            // 6.5) 경사 지형용 집 받침 기둥 생성
            // ==============================
            // 집 바닥 높이는 HouseFloorHeightBlocks 기준 사용
            {
                if (HouseFloorHeightBlocks > 0)
                {
                    // 기둥을 전체 바닥에 다 까는 대신,
                    // - 네 모서리
                    // - 문 앞쪽 중앙
                    // 위주로 "기둥 묶음(lXl 느낌)"만 깔아서 자연스럽게
                    TArray<FIntPoint> PillarBasePoints;

                    // 네 모서리
                    PillarBasePoints.Add(FIntPoint(HouseStartX, HouseStartY));
                    PillarBasePoints.Add(FIntPoint(HouseEndX, HouseStartY));
                    PillarBasePoints.Add(FIntPoint(HouseStartX, HouseEndY));
                    PillarBasePoints.Add(FIntPoint(HouseEndX, HouseEndY));

                    // 앞쪽 중앙 (문이 있는 쪽: StartY 라인 기준)
                    const int32 PillarCenterX = (HouseStartX + HouseEndX) / 2;
                    PillarBasePoints.Add(FIntPoint(PillarCenterX, HouseStartY));

                    // 기둥 묶음 반경 (1이면 3x3, 0이면 1x1)
                    const int32 PillarRadius = 1;

                    for (const FIntPoint& Base : PillarBasePoints)
                    {
                        for (int32 DX = -PillarRadius; DX <= PillarRadius; ++DX)
                        {
                            for (int32 DY = -PillarRadius; DY <= PillarRadius; ++DY)
                            {
                                const int32 PX = Base.X + DX;
                                const int32 PY = Base.Y + DY;

                                if (PX < 0 || PX >= Width || PY < 0 || PY >= Height)
                                {
                                    continue;
                                }

                                const int32 Index = ToIndex(PX, PY);
                                const int32 ColumnHeight = HeightMap[Index];

                                // 땅이 아예 없으면 패스
                                if (ColumnHeight <= 0)
                                {
                                    continue;
                                }

                                // 이미 지형이 집 바닥보다 높거나 같은 경우 → 굳이 기둥 안 세움
                                if (ColumnHeight >= HouseFloorHeightBlocks)
                                {
                                    continue;
                                }

                                // ColumnHeight ~ HouseFloorHeightBlocks-1 까지 기둥 세우기
                                for (int32 Z = ColumnHeight; Z < HouseFloorHeightBlocks; ++Z)
                                {
                                    FVector PillarLocation(
                                        PX * BlockSize,
                                        PY * BlockSize,
                                        Z * BlockSize + BlockSize * 0.5f
                                    );

                                    FTransform PillarTransform(
                                        FRotator::ZeroRotator,
                                        PillarLocation,
                                        FVector(1.f)
                                    );

                                    if (OakPlanksBlocks)
                                    {
                                        OakPlanksBlocks->AddInstance(PillarTransform);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // ────────────────────────────────
            // 7) 지붕 (박공지붕 - OakRoofStairsBlocks)
            // ────────────────────────────────

            // 기존
            // const int32 RoofLayers = FMath::Clamp(UseSizeY / 2, 1, 4);

            // 수정
            const int32 RoofLayers = (UseSizeY / 2) + 1;

            for (int32 Layer = 0; Layer < RoofLayers; ++Layer)
            {
                const int32 YFront = StartY + Layer;
                const int32 YBack = EndY - Layer;

                const float LayerZ = CeilingZ + Layer * BlockSize;

                for (int32 HX = StartX; HX <= EndX; ++HX)
                {
                    // 앞 지붕
                    {
                        FVector Loc(HX * BlockSize, YFront * BlockSize, LayerZ);
                        OakRoofStairsBlocks->AddInstance(
                            FTransform(FRotator(0, 0, 0), Loc, FVector(1.f))
                        );
                    }

                    // 뒤 지붕
                    {
                        FVector Loc(HX * BlockSize, YBack * BlockSize, LayerZ);
                        OakRoofStairsBlocks->AddInstance(
                            FTransform(FRotator(0, 180, 0), Loc, FVector(1.f))
                        );
                    }
                }
            }

            // 지붕 꼭대기 평지
            const float RoofTopZ = CeilingZ + RoofLayers * BlockSize;

            for (int32 HX = StartX + 1; HX <= EndX - 1; ++HX)
            {
                for (int32 HY = StartY + RoofLayers; HY <= EndY - RoofLayers; ++HY)
                {
                    FVector TopLoc(HX * BlockSize, HY * BlockSize, RoofTopZ);
                    OakPlanksBlocks->AddInstance(FTransform(FRotator::ZeroRotator, TopLoc));
                }
            }

            // ==============================
            // 8) 문 앞 계단 (Entry Stairs)
            // ==============================
            if (bGenerateSampleHouse && OakEntryStairsBlocks)
            {
                // 집 앞 방향을 StartY 쪽(앞벽)이라고 가정
                const int32 OutsideX = DoorX;
                const int32 OutsideY = StartY - 1;   // 문 바로 앞 한 칸

                // 청크 내부인지 확인
                if (OutsideX >= 0 && OutsideX < Width &&
                    OutsideY >= 0 && OutsideY < Height)
                {
                    const int32 OutIndex = ToIndex(OutsideX, OutsideY);
                    const int32 OutColumnHeight = HeightMap[OutIndex];

                    if (OutColumnHeight > 0)
                    {
                        // 밖 타일의 지면 윗면
                        const float OutsideTopZ =
                            (OutColumnHeight - 1) * BlockSize + BlockSize * 0.5f;

                        // 계단이 살짝 위/아래로 겹치지 않게 약간만 띄우고 싶다면 +1.f 정도 줄 수도 있음
                        const float StairZ = OutsideTopZ; // 또는 OutsideTopZ + 1.f

                        FVector StairLocation(
                            OutsideX * BlockSize,
                            OutsideY * BlockSize,
                            StairZ
                        );

                        // 좌표계를 기준으로:
                        // X: 앞/뒤, Y: 좌/우 라면, 앞벽이 StartY 쪽(더 작은 Y)이니까
                        // 계단이 집 안쪽(+Y)을 바라보도록 → Yaw = 0 또는 180 중 하나 써야 함.
                        // 우리가 벽을 StartY 쪽을 "앞"으로 잡았다면, 계단은 +Y(집 안쪽)를 향하게:
                        FRotator StairRot(0.f, 0.f, 0.f);
                        // 만약 뒤집혀 있으면 0 대신 180으로 바꿔봐:
                        // FRotator StairRot(0.f, 180.f, 0.f);

                        FTransform StairTransform(
                            StairRot,
                            StairLocation,
                            FVector(1.f)
                        );

                        OakEntryStairsBlocks->AddInstance(StairTransform);
                    }
                }
            }
            // ==============================
        // 9) 집 주변 울타리(Fence) 생성
            if (bGenerateHouseFence &&
                OakFenceBoth && OakFenceCenter && OakFenceCorner && OakFenceOneSide &&
                HouseStartX >= 0 && HouseStartY >= 0)
            {
                // 9-1) 울타리를 둘 타일 집합 만들기 (집에서 HouseFenceOffset 만큼 띄운 사각형 테두리)
                TSet<FIntPoint> FenceCells;

                const int32 FenceOffset = FMath::Max(HouseFenceOffset, 1);

                int32 FenceMinX = FMath::Clamp(HouseStartX - FenceOffset, 0, Width - 1);
                int32 FenceMaxX = FMath::Clamp(HouseEndX + FenceOffset, 0, Width - 1);
                int32 FenceMinY = FMath::Clamp(HouseStartY - FenceOffset, 0, Height - 1);
                int32 FenceMaxY = FMath::Clamp(HouseEndY + FenceOffset, 0, Height - 1);

                // 앞쪽 방향: StartY 쪽(문 있는 쪽)이라고 가정
                const int32 FenceFrontY = FenceMinY;

                // 문 위치 기준으로 게이트(울타리 끊김) 만들기
                const int32 GateCenterX = DoorX;
                const int32 GateHalfWidth = 1; // 게이트 폭: 3타일 (center ±1)

                auto IsGateCell = [&](int32 X, int32 Y) -> bool
                    {
                        if (Y != FenceFrontY)
                        {
                            return false;
                        }
                        return (X >= GateCenterX - GateHalfWidth &&
                            X <= GateCenterX + GateHalfWidth);
                    };

                // 상하 테두리
                for (int32 X = FenceMinX; X <= FenceMaxX; ++X)
                {
                    if (!IsGateCell(X, FenceFrontY))
                    {
                        FenceCells.Add(FIntPoint(X, FenceMinY));
                    }
                    FenceCells.Add(FIntPoint(X, FenceMaxY));
                }

                // 좌우 테두리
                for (int32 Y = FenceMinY + 1; Y <= FenceMaxY - 1; ++Y)
                {
                    FenceCells.Add(FIntPoint(FenceMinX, Y));
                    FenceCells.Add(FIntPoint(FenceMaxX, Y));
                }

                // 9-2) 이 타일들은 식생 금지 구역에도 포함 (나중에 나무 안 박히게)
                for (const FIntPoint& P : FenceCells)
                {
                    HouseNoVegArea.Add(P);
                }

                // 9-3) FenceCells 기반으로 이웃 검사해서 어떤 메쉬를 쓸지 결정
                auto HasFenceAt = [&](int32 FX, int32 FY) -> bool
                    {
                        return FenceCells.Contains(FIntPoint(FX, FY));
                    };

                for (const FIntPoint& Cell : FenceCells)
                {
                    const int32 X = Cell.X;
                    const int32 Y = Cell.Y;

                    // 🔹 이 타일의 지형 높이 가져오기 (없으면 집 바닥 높이 사용)
                    const int32 HIndex = ToIndex(X, Y);
                    int32 ColumnHeight = HouseFloorHeightBlocks;
                    if (HeightMap.IsValidIndex(HIndex))
                    {
                        ColumnHeight = HeightMap[HIndex];
                    }

                    // 지면 윗면의 "중심 높이" (Vegetation에서 쓰는 것과 동일 방식)
                    const float TileGroundTopZ =
                        (ColumnHeight - 1) * BlockSize + BlockSize * 0.5f;

                    // 펜스 메쉬의 피벗이 중앙에 있어서 땅에 반쯤 박혔다면
                    // 한 블록(또는 0.5블록) 위로 올려준다.
                    const float FenceBaseZ =
                        TileGroundTopZ + HouseFenceHeightBlocks * BlockSize;

                    // 이웃 방향 체크 (위/아래/좌/우)
                    const bool bHasNorth = HasFenceAt(X, Y + 1);
                    const bool bHasSouth = HasFenceAt(X, Y - 1);
                    const bool bHasEast = HasFenceAt(X + 1, Y);
                    const bool bHasWest = HasFenceAt(X - 1, Y);

                    int32 NeighborCount = 0;
                    if (bHasNorth) ++NeighborCount;
                    if (bHasSouth) ++NeighborCount;
                    if (bHasEast)  ++NeighborCount;
                    if (bHasWest)  ++NeighborCount;

                    UInstancedStaticMeshComponent* TargetComp = nullptr;
                    FRotator YawRot(0.f, 0.f, 0.f);

                    // ===== 메쉬 선택 규칙 =====
                    if (NeighborCount == 0)
                    {
                        TargetComp = OakFenceCenter;
                        YawRot = FRotator::ZeroRotator;
                    }
                    else if (NeighborCount == 1)
                    {
                        TargetComp = OakFenceOneSide;

                        if (bHasEast)       YawRot = FRotator(0.f, 0.f, 0.f);
                        else if (bHasWest)  YawRot = FRotator(0.f, 180.f, 0.f);
                        else if (bHasNorth) YawRot = FRotator(0.f, 90.f, 0.f);
                        else if (bHasSouth) YawRot = FRotator(0.f, -90.f, 0.f);
                    }
                    else if (NeighborCount == 2)
                    {
                        const bool bVertical = (bHasNorth && bHasSouth);
                        const bool bHorizontal = (bHasEast && bHasWest);

                        if (bVertical || bHorizontal)
                        {
                            TargetComp = OakFenceBoth;

                            if (bHorizontal)
                            {
                                YawRot = FRotator(0.f, 0.f, 0.f);
                            }
                            else
                            {
                                YawRot = FRotator(0.f, 90.f, 0.f);
                            }
                        }
                        else
                        {
                            TargetComp = OakFenceCorner;

                            if (bHasEast && bHasNorth)       YawRot = FRotator(0.f, 0.f, 0.f);
                            else if (bHasNorth && bHasWest)  YawRot = FRotator(0.f, 90.f, 0.f);
                            else if (bHasWest && bHasSouth)  YawRot = FRotator(0.f, 180.f, 0.f);
                            else if (bHasSouth && bHasEast)  YawRot = FRotator(0.f, -90.f, 0.f);
                        }
                    }
                    else
                    {
                        TargetComp = OakFenceCenter;
                        YawRot = FRotator::ZeroRotator;
                    }

                    if (!TargetComp)
                    {
                        continue;
                    }

                    // 🔹 펜스 위치: 지면 기준으로 띄운 높이
                    FVector FenceLocation(
                        X * BlockSize,
                        Y * BlockSize,
                        FenceBaseZ
                    );

                    FTransform FenceTransform(
                        YawRot,
                        FenceLocation,
                        FVector(1.f)
                    );

                    TargetComp->AddInstance(FenceTransform);

                    // 🪵 Fence 아래에 Oak_Log 기둥 추가 (원하면)
                    if (OakLogPillars)
                    {
                        // 이전: 지면 중심에서 -0.5블록 (반칸 낮음)
                        // 변경: 반칸 올림 -> 로그 중심을 지면 중심과 일치시킴
                        const float LogZ = TileGroundTopZ; // was: TileGroundTopZ - BlockSize * 0.5f

                        FVector LogLocation(
                            X * BlockSize,
                            Y * BlockSize,
                            LogZ
                        );

                        // 기존: Z 스케일 2.0으로 한 블록 높이로 보정 유지
                        FTransform LogTransform(
                            FRotator::ZeroRotator,
                            LogLocation,
                            FVector(1.f, 1.f, 1.f)
                        );

                        OakLogPillars->AddInstance(LogTransform);
                    }
                }


            } // 끝: bGenerateHouseFence
        }
    }

    void AMinecraftTerrainActor::Tick(float DeltaTime)
    {
        Super::Tick(DeltaTime);

    }





