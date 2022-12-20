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
void ManageMotionBlur(void)
{
     if(counter == 3)
      counter = 0;
    else
      counter++;
}

int main()
{

  HalCreate();

  // CreateECSTest();

  
  str[0] = 'a';

  screen = memAlloc(COLUMNS * ROWS, MEMF_ANY);
  zbuffer = memAlloc(COLUMNS * ROWS, MEMF_ANY);
  map = memAlloc(256*256*2, MEMF_ANY);

  GenMap();

  Angles();
  Height();
  GenDither64();

  playerX = 50;
  playerZ = 30;


  while (1)
  {
    ManageMotionBlur();

    counter2++;
    //TransformMap(counter2, 0, 0, 100, 30);
    HalProcess();

    playerY ++;
    
    PathTracing(playerX, playerY, playerZ);
    ScreenToPlanes64(screen, planes, counter, 0);
    //ScreenToPlanes64(zbuffer, planes, counter, 128);

    //printFont(160, 200, str, 0);
    ReadInputs();
    //ConvertIntToChar(playerX, str, 3);
    //printFont(160, 200, str, 15);

    // Update the entity
    // updateEntities(&g_Entities);
  }
  HalDestroy();

  return 0;
}


/* switch(eState) {
    case STATE_MENU: menuLoop(); break;
    case STATE_GAME: gameLoop(); break;
  }*/
