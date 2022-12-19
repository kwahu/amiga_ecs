#define AMIGA 1

#include "types.h"
#include "std.h"
#include "hal.h"
#include "component_types.h"
#include "ecs.h"
#include "ecs_test.h"
#include "tracing.h"
#include "c2p.h"

tECS g_Entities;

unsigned char joyUp, joyDown, joyLeft, joyRight, joyFire;

unsigned char counter, counter2;
unsigned char playerY, playerX, playerZ;

char str[3];

/*  void DrawScreen(unsigned char counter)
  {
      for(int x = 0; x < COLUMNS; x++)
       {
           for(int y = 0; y < ROWS; y++)
           {
               screen[x+y*COLUMNS] = zbuffer[x][y];//map[x*4][y*2];//x+y+counter;
           }
       }
  }*/

void ReadInputs()
{
  ProcessInput();
  if (joyUp)
  {
    playerZ++;
    *(planes[0] + 32000) = (unsigned char)0xff;
    str[0] = 'u';
  }
  else if (joyDown)
  {
    playerZ--;
    *(planes[0] + 32000) = (unsigned char)0x00;
    str[0] = 'd';
  }
    else if (joyLeft)
  {
    playerX--;
    *(planes[0] + 32000) = (unsigned char)0x00;
    str[0] = 'd';
  }
    else if (joyRight)
  {
    playerX++;
    *(planes[0] + 32000) = (unsigned char)0x00;
    str[0] = 'd';
  }
  else
  {
    str[0] = 'n';
  }
}

int main()
{

  HalCreate();

  // CreateECSTest();

  
  str[0] = 'a';

  screen = memAlloc(COLUMNS * ROWS, MEMF_ANY);
  zbuffer = memAlloc(COLUMNS * ROWS, MEMF_ANY);

  GenMap();

  Angles();
  Height();
  GenDither64();

  playerX = 128;


  while (1)
  {
    if(counter == 3)
      counter = 0;
    else
      counter++;

    counter2++;
    //TransformMap(counter2, 0, 0, 100, 30);
    HalProcess();
    
    
    PathTracing(playerX, playerY, playerZ);
    // DrawScreen(counter);
    ScreenToPlanes64(screen, planes, counter, 128);
    ScreenToPlanes64(zbuffer, planes, counter, 0);
    //MovePlanesToChip();
    

    printFont(160, 200, str, 0);
    ReadInputs();
    ConvertIntToChar(playerX, str, 3);
    printFont(160, 200, str, 15);

    // vPortWaitForEnd(s_pPlayVPort);
    //  Clear the buffer
    // simpleBufferClear(s_pPlayBfr);

    // MovePlanesToChip();

    // Update the entity
    // updateEntities(&g_Entities);

    // ConvertIntToChar(entities->pEntities[0].pComponents[0].data, str, 3);

    // 
  }
  HalDestroy();

  return 0;
}

/* switch(eState) {
    case STATE_MENU: menuLoop(); break;
    case STATE_GAME: gameLoop(); break;
  }*/
