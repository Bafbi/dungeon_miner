#pragma once

#include "../utils/utils.h"

typedef struct Entity
{
    Pos pos;
    int health;
} Entity;

/*
// Change la position de l'entité
//
// entity: L'entité dont que l'ont veux bouger
// x: les nombre de case sur l'axe x dont l'entité bouge
// y: les nombre de case sur l'axe y dont l'entité bouge
*/
void entity_setPos(Entity *entity, Pos pos)
{
    entity->pos.x = pos.x;
    entity->pos.y = pos.y;
}

/**
 * @brief Enleve de la vie à l'entité
 * @param entity L'entité sur la quelle on veux enlever de la vie
 * @param qty La quantité de vie à enlever à l'entité
 * @return void
 */
void entity_memoveHp(Entity *entity, int qty)
{
    entity->health -= qty;
}