#pragma once
#include <unordered_map>
#include <queue>
#include <memory>
#include "Core/Types.hpp"

struct ChunkPos
{
    int x, y;

    bool operator==(const ChunkPos& other) const
    {
        return x == other.x && y == other.y;
    }
};
struct ChunkPosHash
{
    size_t operator()(const ChunkPos& p) const
    {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

struct DrawChunkData
{
    s32 pos[2];
    u32 data[2];
};

class Chunk
{
public:
    Chunk(s32 _x, s32 _y, u64 _data);
    ~Chunk();

    union
    {
        struct
        {
            s32 x;
            s32 y;
	        u64	data;
        };
        DrawChunkData drawData;
    };

    Chunk* up;
    Chunk* down;
    Chunk* right;
    Chunk* left;
    Chunk* upRight;
    Chunk* downRight;
    Chunk* upLeft;
    Chunk* downLeft;
    u64 life;//If the life goes past a specific value, it kills the chunk

    void Update(std::unique_ptr<Chunk>& _edit);
    void CreateNewChunks(std::queue<ChunkPos>& _toAdd);
    bool ShouldDelete();
    
    void DoLinks(std::unordered_map<ChunkPos, std::unique_ptr<Chunk>, ChunkPosHash>& _target);
    static Chunk* Get(ChunkPos _xy, std::unordered_map<ChunkPos, std::unique_ptr<Chunk>, ChunkPosHash>& _chunks);
};