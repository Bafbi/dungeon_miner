#pragma once

typedef enum BlockType
{
    air_block,
    stone_block,
    iron_block,
    coal_block,
    mytrile_block
} BlockType;

int BlockColor[] = {0, 7, 15, 8, 5};

char DurabilityTexture[] = {' ', 176, 177, 178, 219};
// char DurabilityTexture[] = {' ', 219, 178, 177, 176};
