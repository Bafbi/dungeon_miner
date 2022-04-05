#pragma once

#include "./block.c"
#include "../utils/pos.c"
#include "./entity.c"
#include "../utils/new_perlin.c"

typedef struct Chunk
{
    Block *blockData;
    Pos position;
    Entity *entity;
} Chunk;

typedef enum SeedType
{
    CAVE_SEED,
    MYTRILE_SEED
} SeedType;

#define CHUNK_SIZE 16

Chunk chunk_generateNew(Pos pos, int generationSeeds[])
{

    Chunk chunk;
    chunk.blockData = malloc(sizeof(Block) * CHUNK_SIZE * CHUNK_SIZE);
    chunk.position = pos;

    SEED = generationSeeds[CAVE_SEED];
    float perlinCave[CHUNK_SIZE * CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++)
    {
        perlinCave[i] = Perlin_Get2d((i % CHUNK_SIZE) + pos.x * CHUNK_SIZE, (i / CHUNK_SIZE) + pos.y * CHUNK_SIZE, 0.2, 1);
    }

    SEED = generationSeeds[MYTRILE_SEED];
    float perlinOre[CHUNK_SIZE * CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++)
    {
        perlinOre[i] = Perlin_Get2d((i % CHUNK_SIZE) + pos.x * CHUNK_SIZE, (i / CHUNK_SIZE) + pos.y * CHUNK_SIZE, 0.1, 1);
    }

    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++)
    {
        int type = perlinCave[i] < 0.5 ? AIR_BLOCK : perlinOre[i] < 0.95 ? STONE_BLOCK
                                                                         : MYTRILE_BLOCK;
        int dura;
        dura = type == AIR_BLOCK ? 0 : perlinCave[i] < 0.7 ? 1
                                   : perlinCave[i] < 0.8   ? 2
                                   : perlinCave[i] < 0.9   ? 3
                                                           : 4;
        Block block = {type, dura};
        chunk.blockData[i] = block;
    }

    return chunk;
}