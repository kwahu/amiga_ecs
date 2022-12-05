#include "ecs.c"

void CreateECSTest()
{
    for(int c=0;c<1000;c++)
    {
        // Create an entity
        unsigned char entityIndex = AddEntity(&g_Entities);

        // Create a component position
       /* tComponent *component = allocateMemory(sizeof(tComponent));
        component->type = COMPONENT_TYPE_POSITION;
        component->data = allocateMemory(sizeof(tComponentTypePosition));
        *((tComponentTypePosition *)component->data) = (tComponentTypePosition){c, c};*/
        g_Entities.entities[entityIndex].position.x = c;

      //  AddComponent(&g_Entities.entities[entityIndex], component);
    }
}