#pragma once

/// Standard lib ///
#include <math.h>
///-------------///

/// My file ///
#include "../class/map.c"
#include "./ConsoleTools.c"
#include "../class/chunk.c"
///--------///

/// Public function ///

///-----------------///

/// Private function ///

/**
 * @brief
 *
 * @param map The map to render
 * @param camPos The relative position in the console to render the map part
 * @param start Starting position of the part of map (corner up-left)
 * @param end Ending position of the part of map (corner bottom-right)
 */
void renderMapPart(Map *map, Pos camPos, Pos start, Pos end);

/**
 * @brief Render a part of a chunk in the console
 *
 * @param chunk The chunk to render
 * @param camPos The relative position in the console to render the chunk part
 * @param start Starting position of the part of chunk (corner up-left)
 * @param end Ending position of the part of chunk (corner bottom-right)
 */
void renderChunk(Chunk chunk, Pos camPos, Pos start, Pos end);

///------------------///

void renderMapPart(Map *map, Pos camPos, Pos start, Pos end)
{
    for (int y = 0; y < (end.y - start.y) / CHUNK_SIZE; y++)
    {
        for (int x = 0; x < (end.x - start.x) / CHUNK_SIZE; x++)
        {
            printf("");
        }
    }
}

void renderChunk(Chunk chunk, Pos camPos, Pos start, Pos end)
{
    for (int y = start.y; y < end.y; y++)
    {
        for (int x = start.x; x < end.x; x++)
        {
            setBackGroundColor(0);
            setWriteColor(BlockColor[chunk.blockData[y * CHUNK_SIZE + x].type]);
            moveCursor(camPos.x + x, camPos.y + y);

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
