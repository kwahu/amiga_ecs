#include "types.h"
#include "std.c"
#include "hal.h"
#include "ecs.h"
#include "component_types.h"
#include "ecs_test.c"
#include "printf.h"

tEntity *g_Entities = NULL;

int main()
{
  halCreate();

  g_Entities = allocateMemory(sizeof(tEntity));
  g_Entities->id = 0;
  g_Entities->components = NULL;
  g_Entities->next = NULL;

  CreateECSTest(g_Entities);

  while (1)
  {
    /* switch(eState) {
       case STATE_MENU: menuLoop(); break;
       case STATE_GAME: gameLoop(); break;
     }*/

    // Update the entity
    update_entities(g_Entities);
    char str[256];
    //ConvertIntToChar(entities->pEntities[0].pComponents[0].data, str, 3);
 
    ConvertIntToChar(((tComponentTypePosition *)g_Entities->next->components->component->data)->x, str, 3);

    printFont(128, 128, str ,1);
  }
  halDestroy();

  return 0;
}