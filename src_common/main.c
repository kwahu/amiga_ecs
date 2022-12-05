#include "types.h"
#include "std.h"
#include "hal.h"
#include "ecs.h"
#include "component_types.h"
#include "ecs_test.c"

tEntityList *g_Entities = NULL;

int main()
{
  halCreate();

  g_Entities = CreateECSTest();

  while (1)
  {

    // Update the entity
    update_entities(g_Entities);
    char str[256];
    str[0] = 'a';
    //ConvertIntToChar(entities->pEntities[0].pComponents[0].data, str, 3);
 
    //ConvertIntToChar(((tComponentTypePosition *)g_Entities->next->entity->components->component->data)->x, str, 3);

    printFont(128, 128, str ,1);
  }
  halDestroy();

  return 0;
}