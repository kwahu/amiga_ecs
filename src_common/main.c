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

char str[15];

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
    //*(planes + 32000) = (unsigned char)0xff;
    str[0] = 'u';
  }
  else if (joyDown)
  {
    playerZ--;
    //*(planes + 32000) = (unsigned char)0x00;
    str[0] = 'd';
  }
    else if (joyLeft)
  {
    playerX--;
    //*(planes[0] + 32000) = (unsigned char)0x00;
    str[0] = 'd';
  }
    else if (joyRight)
  {
    playerX++;
    //*(planes[0] + 32000) = (unsigned char)0x00;
    str[0] = 'd';
  }
  else
  {
    str[0] = 'n';
  }
}
void ManageMotionBlur(unsigned char value)
{
     if(counter == value-1)
      counter = 0;
    else
      counter++;
}



int main()
{

  SetCopperChunky(0);


  HalCreate();

  // CreateECSTest();

  screenByte = memAlloc(COLUMNS * ROWS, MEMF_ANY);
  screenWord = memAlloc(COLUMNS * ROWS * 2, MEMF_ANY);
  zbuffer = memAlloc(COLUMNS * ROWS, MEMF_ANY);
  map = memAlloc(MAPWIDTH*MAPLENGTH*2, MEMF_ANY);

  pAnglesByte = memAlloc(COLUMNS * DEPTH, MEMF_ANY);
  //pHeightsByte = memAlloc(ROWS * DEPTH, MEMF_ANY);

  GenMap();

  AnglesByte();
  HeightByte();

  //GenDither2x2();
  GenDither4x4();
  GenDither4x4Shifted();

  //CalculateRayCasts();

  playerX = 50;
  playerY = 0;
  playerZ = 10;



  while (1)
  {
    ManageMotionBlur(4);

    

    counter2++;
    //TransformMap(counter2, 64, 16, 48, 16);
    HalProcess();

    //

    //playerY ++;

   // playerZ = *(map+playerX*2+playerY*MAPWIDTH*2) + 10;

    PathTracingWordPointer(playerX/4, playerY, playerZ/4);

    //40x8x8
     if(GetCopperChunky())
       copperTest(); //25,69
     else
      //ScreenToPlanes2x2((unsigned char*)screenWord, planes, counter, 0*4); 
      ScreenToPlanes4x4((unsigned char*)screenWord, planes, counter, 0*4);  //18,81
      //ScreenToPlanesUnrolledWholeWord((unsigned char*)screenWord, planes, counter, 0*4);  //14,46
      //ScreenToPlanesTopDown((unsigned char*)screenWord, planes, counter, 0*4);  //14,46
      //ScreenToPlanesWordWord((unsigned char*)screenWord, planes, counter, 0*4);  //11,48
      //ScreenToPlanesUnrolledByte((unsigned char*)screenWord, planes, counter, 0*4);  //11,56
      //ScreenToPlanesUnrolledWord((unsigned char*)screenWord, planes, counter, 0*4);  //14,46

    //PathTracingByte(playerX, playerY, playerZ);
    

    

    // for(unsigned char x=0; x<COLUMNS; x++)
    // {
    //   for(unsigned char y=0; y<ROWS; y++)
    //   {
    //     *(screenWord+x+y*COLUMNS) = (x) % 32;
    //   }
    // }
    //ScreenToPlanesWord(screenByte, planes, counter, 0);
    //ScreenToPlanesWordWord((unsigned char*)screenWord, planes, counter, 0);
    //ScreenToPlanesTopDown((unsigned char*)screenWord, planes, counter, 0);
    //ScreenToPlanes64(zbuffer, planes, counter, 128);

    //printFont(160, 50, str, 0);
    printFont(50, 50, str, 15);
    ReadInputs();
    GetDeltaTime(str);
    //ConvertIntToChar(playerX, str, 3);
    //printFont(160, 150, str, 15);

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
