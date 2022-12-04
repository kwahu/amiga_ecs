#ifndef _ECS_H_
#define _ECS_H_

#include "types.h"

typedef struct _tComponentList tComponentList;
typedef struct _tEntity tEntity;

typedef struct _tComponent
{
    unsigned char type;
    void *data;
} tComponent;

typedef struct _tComponentList
{
    tComponent *component;
    tComponentList *next;
} tComponentList;

typedef struct _tEntity
{
    unsigned short int id;
    tComponentList *components;
    tEntity *next;
} tEntity;
/*
typedef struct _tEntityList
{
    tEntity *entity;
    tEntityList *next;
} tEntityList;
*/
// adding a component to an entity
void add_component(tEntity *entity, tComponent *component);

// retrieving a component from an entity.
tComponent *get_component(tEntity *entity, int type);

// updating the entities and their components.
void update_entities(tEntity *entities);


#endif