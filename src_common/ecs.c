#ifndef _ECS_C_
#define _ECS_C_
//#include <stdlib.h>
#include "hal.h"
#include "ecs.h"
#include "component_types.h"

// Define a function for adding an entity to the array
// possioble to have multiple arrays of entities for different purposes
unsigned char AddEntity(tECS *entities)
{
    //return last index
    return entities->numEntities++;
}




//update all entities
void updateEntities(tECS *entities)
{
    // Iterate over the entities
    for (int i = 0; i < entities->numEntities; i++)
    {
        entities->entities[i].position.x += 1;
    }
}

#endif