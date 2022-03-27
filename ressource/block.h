#pragma once

typedef enum BlockType
{
    AIR_BLOCK,
    STONE_BLOCK,
    IRON_BLOCK,
    COAL_BLOCK,
    MYTRILE_BLOCK
} BlockType;

const int BlockColor[] = {0, 7, 15, 8, 5};

const char DurabilityTexture[] = {' ', 176, 177, 178, 219};
// char DurabilityTexture[] = {' ', 219, 178, 177, 176};
