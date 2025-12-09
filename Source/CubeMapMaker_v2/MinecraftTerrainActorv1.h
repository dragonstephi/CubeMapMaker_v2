// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"



#include "MinecraftTerrainActorv1.generated.h"


UCLASS()
class CUBEMAPMAKER_V2_API AMinecraftTerrainActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain")
	int32 Width = 10;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain")
	int32 Height = 10;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain")
	float BlockSize = 100.f;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain")
	int32 MaxHeight = 1;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain")
	int32 Seed = 12345;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain")
	float NoiseScale = 0.1f;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain")
	float HeightMultiplier = 10.0f;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain")
	int32 BaseHeight = 30;   // 전체 지형을 위로 올리는 기본 높이(블록 단위)

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Chunk")
	int32 ChunkOffsetX = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Chunk")
	int32 ChunkOffsetY = 0;

public:
	// --- Vegetation components ---

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	UInstancedStaticMeshComponent* GrassFoliage;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	UInstancedStaticMeshComponent* FlowerDandelion;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	UInstancedStaticMeshComponent* FlowerDaisy;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	UInstancedStaticMeshComponent* FlowerPoppy;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	UInstancedStaticMeshComponent* TreeType1;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	UInstancedStaticMeshComponent* TreeType2;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	UInstancedStaticMeshComponent* TreeType3;


	// --- Vegetation spawn settings ---

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	float GrassDensity = 0.3f;      // 0~1 사이 추천

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	float FlowerDensity = 0.15f;    // 0~1

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	float TreeDensity = 0.03f;      // 0~1

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Vegetation")
	int32 VegetationSeedOffset = 1000;   // Seed + 이 값으로 랜덤 분리

	// --- Biome & Water settings --- 
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Biome")
	float BiomeNoiseScale = 0.02f;   // 바이옴 구분 크기

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Biome", meta = (ClampMin = "-100.0", ClampMax = "200.0"))
	float BeachHeightMultiplier = 6.0f;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Biome")
	int32 SeaLevelBlocks = 4;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Water", meta = (ClampMin = "0", ClampMax = "4"))
	int32 WaterNeighborRequired = 2; // 주변 몇 칸이 높아야 물 허용할지 (0~4)

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Water")
	bool bWaterSimpleMode = true;    // 체크하면 이웃 검사 없이 물 많이 깔리는 모드

	// --- Building blocks ---
	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Building")
	UHierarchicalInstancedStaticMeshComponent* OakPlanksBlocks;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Building")
	UHierarchicalInstancedStaticMeshComponent* GlassBlocks;

	UPROPERTY(VisibleAnywhere, Category = "A_MinecraftTerrain|House")
	UHierarchicalInstancedStaticMeshComponent* OakRoofStairsBlocks;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|House")
	UHierarchicalInstancedStaticMeshComponent* OakEntryStairsBlocks;

	// --- Sample House Settings ---
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House")
	bool bGenerateSampleHouse = true;    // 체크 끄면 집 안 만듦

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseSizeX = 7;                // 블록 단위 가로

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseSizeY = 7;                // 블록 단위 세로

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseWallHeight = 3;           // 벽 높이(블록)

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseCenterOffsetX = 0;        // 청크 중앙 기준 오프셋
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseCenterOffsetY = 0;
	// 집 영역(식생 금지 구역) 저장
	TSet<FIntPoint> HouseNoVegArea;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseStartX = -1;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseEndX = -1;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseStartY = -1;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseEndY = -1;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseFloorHeightBlocks = 0;

	// 집 주변을 얼마나 넓게 평탄화할지 (기본 3줄)
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House")
	int32 HouseFlattenMargin = 3;

	// --- 수평(각 벽) 창문 설정 ---
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Horizontal")
	int32 FrontWindowCount = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Horizontal")
	int32 BackWindowCount = 3;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Horizontal")
	int32 LeftWindowCount = 3;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Horizontal")
	int32 RightWindowCount = 3;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Horizontal")
	int32 FrontWindowCenterOffset = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Horizontal")
	int32 BackWindowCenterOffset = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Horizontal")
	int32 LeftWindowCenterOffset = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Horizontal")
	int32 RightWindowCenterOffset = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Horizontal")
	bool bAllowFrontWindowsNearDoor = false;

	// --- 수직(층) 창문 설정 ---
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical", meta = (ClampMin = "1", ClampMax = "5"))
	int32 WindowRowCount = 1;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical", meta = (ClampMin = "1"))
	int32 FirstWindowHeightBlock = 2;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical", meta = (ClampMin = "1"))
	int32 WindowRowSpacingBlocks = 2;

	// 벽별 수직 오프셋 (블록 단위)
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical")
	int32 FrontWindowVerticalOffsetBlocks = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical")
	int32 BackWindowVerticalOffsetBlocks = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical")
	int32 LeftWindowVerticalOffsetBlocks = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical")
	int32 RightWindowVerticalOffsetBlocks = 0;

	// 면별 RowCount Override (0이면 Global WindowRowCount 사용)
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical")
	int32 FrontWindowRowCountOverride = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical")
	int32 BackWindowRowCountOverride = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical")
	int32 LeftWindowRowCountOverride = 0;

	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|House|Window|Vertical")
	int32 RightWindowRowCountOverride = 0;



public:
	UPROPERTY(VisibleAnywhere)
	class UHierarchicalInstancedStaticMeshComponent* GrassBlocks;

	UPROPERTY(VisibleAnywhere)
	class UHierarchicalInstancedStaticMeshComponent* DirtBlocks;

	UPROPERTY(VisibleAnywhere)
	class UHierarchicalInstancedStaticMeshComponent* SandBlocks;

	UPROPERTY(VisibleAnywhere)
	class UHierarchicalInstancedStaticMeshComponent* CobblestoneBlocks;

	UPROPERTY(VisibleAnywhere)
	class UHierarchicalInstancedStaticMeshComponent* WaterBlocks;

	// --- House Fence Settings ---
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Fence")
	bool bGenerateHouseFence = true;          // 집 주변 울타리 생성 여부

	// 집 바깥으로 얼마나 띄워서 울타리를 둘지 (집 벽에서 몇 타일 떨어져서)
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Fence")
	int32 HouseFenceOffset = 2;

	// 펜스 높이(블록 단위) - 에디터에서 조정 가능
	UPROPERTY(EditAnywhere, Category = "A.MinecraftTerrain|Fence", meta = (ClampMin = "0", ClampMax = "10"))
	int32 HouseFenceHeightBlocks = 1;

	// 펜스 메쉬들
	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Fence")
	UInstancedStaticMeshComponent* OakFenceBoth;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Fence")
	UInstancedStaticMeshComponent* OakFenceCenter;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Fence")
	UInstancedStaticMeshComponent* OakFenceCorner;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Fence")
	UInstancedStaticMeshComponent* OakFenceOneSide;

	UPROPERTY(VisibleAnywhere, Category = "A.MinecraftTerrain|Fence")
	UInstancedStaticMeshComponent* OakLogPillars;



public:
	// Sets default values for this actor's properties
	AMinecraftTerrainActor();

protected:
	// Called when the game starts or when spawned
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
