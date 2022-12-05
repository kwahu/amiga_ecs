#ifndef _ECS_H_
#define _ECS_H_

#include "types.h"
#include "component_position.c"

#define MAX_ENTITIES 1000
#define MAX_COMPONENTS 10

typedef struct _tComponent
{
    unsigned char type;
    void *data;
} tComponent;

typedef struct _tEntity
{
    unsigned char numComponents; //additionally it defines if the entity is active or not
    //tComponent* components[MAX_COMPONENTS];
    tComponentTypePosition position;
} tEntity;

typedef struct _tECS
{
    tEntity entities[MAX_ENTITIES];
    unsigned char numEntities;
} tECS;

tECS g_Entities;

unsigned char AddEntity(tECS *entities);

#endif