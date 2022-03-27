#pragma once

/// Standard lib ///
#include <math.h>
///-------------///

/// My file ///
#include "./class/map.c"
#include "./utils/ConsoleTools.c"
///--------///

/// Public function ///
/**
 * @brief Use to render the game in the console
 *
 * @param map The pointer of the game map to render
 */
void render(Map *map);
///-----------------///

/**
 * @brief Render a part of a chunk in the console
 *
 * @param chunk The chunk to render
 * @param displayPos The relative position in the console to render the chunk
 * @param start Starting position of the part of chunk (corner up-left)
 * @param end Ending position of the part of chunk (corner bottom-right)
 */
static void renderChunk(Chunk chunk, Pos displayPos, Pos start, Pos end);

void render(Map *map)
{
    COORD consoleSize = getConsoleSize();
    Pos displayRelativePos = {consoleSize.X / 2, consoleSize.Y / 2};
    Pos playerPos = map->player.entityData.pos;
    Pos playerDisplayPos = addPos(playerPos, displayRelativePos);
    Pos playerChunkPos = {floor((float)playerPos.x / (float)CHUNK_SIZE),
                          floor((float)playerPos.y / (float)CHUNK_SIZE)};
    Chunk *chunk = getChunk(map, playerChunkPos);
    Pos pos1 = {0, 0};
    Pos pos2 = {16, 16};
    Pos posTmp = {CHUNK_SIZE, CHUNK_SIZE};
    Pos chunkDisplayPos = addPos(displayRelativePos, multiplyPos(playerChunkPos, posTmp));

    renderChunk(*chunk, chunkDisplayPos, pos1, pos2);

    moveCursor(playerDisplayPos.x, playerDisplayPos.y);
    if (map->player.entityData.light)
    {
        setBackGroundColor(YELLOW);
    }
    else
        setBackGroundColor(0);
    setWriteColor(15);
    plotChar(PLAYER_TEXTURE);
    moveCursor(0, 16 + 1);
}

static void renderChunk(Chunk chunk, Pos displayPos, Pos start, Pos end)
{
    for (int y = start.y; y < end.y; y++)
    {
        for (int x = start.x; x < end.y; x++)
        {
            setBackGroundColor(0);
            setWriteColor(BlockColor[chunk.blockData[y * CHUNK_SIZE + x].type]);
            moveCursor(displayPos.x + x, displayPos.y + y);

            Pos posI = {x, y};

            if (chunk.blockData[y * CHUNK_SIZE + x].type != AIR_BLOCK)
            {
                plotChar(DurabilityTexture[chunk.blockData[y * CHUNK_SIZE + x].durability]);
            }
            else
                plotChar(' ');
        }
    }
}
