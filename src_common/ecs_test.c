#include "ecs.c"

void CreateECSTest()
{
    for(int c=0;c<1000;c++)
    {
        // Create an entity
        unsigned char entityIndex = AddEntity(&g_Entities);

        g_Entities.entities[entityIndex].position.x = c;
    }
}