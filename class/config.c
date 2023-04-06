#pragma once

#include <stdio.h>

typedef struct Config
{
    int loadDistance;
} Config;

Config *config_init_ptr(int loadDistance)
{
    Config *config;
    config = malloc(sizeof(Config));
    config->loadDistance = loadDistance;
}
