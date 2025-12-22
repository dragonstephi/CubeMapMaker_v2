#include "VoxelMesher.h"

namespace VoxelMesher
{
    void AddQuad(
        TArray<FVector>& Verts,
        TArray<int32>& Tris,
        TArray<FVector>& Normals,
        TArray<FVector2D>& UV0,
        TArray<FProcMeshTangent>& Tangents,
        const FVector& A, const FVector& B, const FVector& C, const FVector& D,
        const FVector& N
    )
    {
        const int32 I = Verts.Num();
        Verts.Add(A); Verts.Add(B); Verts.Add(C); Verts.Add(D);

        Tris.Add(I + 0); Tris.Add(I + 1); Tris.Add(I + 2);
        Tris.Add(I + 0); Tris.Add(I + 2); Tris.Add(I + 3);

        Normals.Add(N); Normals.Add(N); Normals.Add(N); Normals.Add(N);

        UV0.Add(FVector2D(0, 0));
        UV0.Add(FVector2D(1, 0));
        UV0.Add(FVector2D(1, 1));
        UV0.Add(FVector2D(0, 1));

        Tangents.Add(FProcMeshTangent(1, 0, 0));
        Tangents.Add(FProcMeshTangent(1, 0, 0));
        Tangents.Add(FProcMeshTangent(1, 0, 0));
        Tangents.Add(FProcMeshTangent(1, 0, 0));
    }

    void BuildTopFacesGreedy(
        int32 Width, int32 Height, float BlockSize, int32 ChunkMaxZ,
        const FVector& ChunkWorldOrigin,
        TFunctionRef<bool(int32, int32, int32)> IsSolid,
        TFunctionRef<uint8(int32, int32, int32)> GetType,
        TArray<FVector>& Verts,
        TArray<int32>& Tris,
        TArray<FVector>& Normals,
        TArray<FVector2D>& UV0,
        TArray<FProcMeshTangent>& Tangents
    )
    {
        auto Idx2D = [&](int32 x, int32 y) { return x + y * Width; };

        TArray<int32> TopZ;   TopZ.SetNum(Width * Height);
        TArray<uint8> TopT;   TopT.SetNum(Width * Height);

        for (int32 y = 0; y < Height; ++y)
            for (int32 x = 0; x < Width; ++x)
            {
                int32 zTop = -1;
                for (int32 z = ChunkMaxZ - 1; z >= 0; --z)
                {
                    if (IsSolid(x, y, z)) { zTop = z; break; }
                }
                TopZ[Idx2D(x, y)] = zTop;
                TopT[Idx2D(x, y)] = (zTop >= 0) ? GetType(x, y, zTop) : 0;
            }

        TArray<uint8> Vis; Vis.Init(0, Width * Height);
        const float BS = BlockSize;

        auto AddTopQuad = [&](int32 x0, int32 y0, int32 w, int32 h, int32 zTop)
            {
                const FVector P0 = ChunkWorldOrigin + FVector((x0)*BS, (y0)*BS, (zTop + 1) * BS);
                const FVector P1 = ChunkWorldOrigin + FVector((x0 + w) * BS, (y0)*BS, (zTop + 1) * BS);
                const FVector P2 = ChunkWorldOrigin + FVector((x0 + w) * BS, (y0 + h) * BS, (zTop + 1) * BS);
                const FVector P3 = ChunkWorldOrigin + FVector((x0)*BS, (y0 + h) * BS, (zTop + 1) * BS);

                AddQuad(Verts, Tris, Normals, UV0, Tangents, P0, P1, P2, P3, FVector(0, 0, 1));
            };

        for (int32 y = 0; y < Height; ++y)
            for (int32 x = 0; x < Width; ++x)
            {
                const int32 i = Idx2D(x, y);
                if (Vis[i]) continue;

                const int32 zTop = TopZ[i];
                const uint8 tTop = TopT[i];

                if (zTop < 0 || tTop == 0) { Vis[i] = 1; continue; }
                if (IsSolid(x, y, zTop + 1)) { Vis[i] = 1; continue; }

                int32 w = 1;
                while (x + w < Width)
                {
                    const int32 j = Idx2D(x + w, y);
                    if (Vis[j]) break;
                    if (TopZ[j] != zTop) break;
                    if (TopT[j] != tTop) break;
                    if (IsSolid(x + w, y, zTop + 1)) break;
                    ++w;
                }

                int32 h = 1;
                bool ok = true;
                while (y + h < Height && ok)
                {
                    for (int32 xx = 0; xx < w; ++xx)
                    {
                        const int32 j = Idx2D(x + xx, y + h);
                        if (Vis[j] || TopZ[j] != zTop || TopT[j] != tTop || IsSolid(x + xx, y + h, zTop + 1))
                        {
                            ok = false; break;
                        }
                    }
                    if (ok) ++h;
                }

                for (int32 yy = 0; yy < h; ++yy)
                    for (int32 xx = 0; xx < w; ++xx)
                        Vis[Idx2D(x + xx, y + yy)] = 1;

                AddTopQuad(x, y, w, h, zTop);
            }
    }
}
