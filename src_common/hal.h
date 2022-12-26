#ifndef _HAL_HAL_H_
#define _HAL_HAL_H_


#include <ace/types.h>
#include <ace/utils/extview.h>
#include <ace/generic/screen.h>
#include <ace/managers/viewport/simplebuffer.h>
#include <ace/utils/font.h>
#include <ace/managers/system.h>

extern  tView *s_pPlayView;
extern  tVPort *s_pPlayVPort;
extern  tSimpleBufferManager *s_pPlayBfr;

extern  tFont *s_pPlayFont;
extern  tTextBitMap *s_pTextBitMap;

#define ECS_BPP 4

extern unsigned char *planes;


void HalCreate();
void HalProcess();
void HalDestroy();
void printFont(int x, int y, char *str, int color);
void* allocateMemory(unsigned short size);
void MovePlanesToChip();
void ProcessInput();
void GetDeltaTime(char str[15]);
void copperTest();

#endif