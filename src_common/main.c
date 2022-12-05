#include "types.h"
#include "std.h"
#include "hal.h"
#include "component_types.h"
#include "ecs_test.c"

int main()
{

  halCreate();

  CreateECSTest();

  char str[256];
  str[0] = 'a';

  while (1)
  {
 

    // Update the entity
    updateEntities(&g_Entities);
    
    //ConvertIntToChar(entities->pEntities[0].pComponents[0].data, str, 3);
 
    //ConvertIntToChar(g_Entities.entities[0].position.x, str, 3);
    

    printFont(128, 128, str ,1);
  }
  halDestroy();

  return 0;
}

   /* switch(eState) {
       case STATE_MENU: menuLoop(); break;
       case STATE_GAME: gameLoop(); break;
     }*/