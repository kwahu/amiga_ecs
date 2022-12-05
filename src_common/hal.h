#ifndef _HAL_HAL_H_
#define _HAL_HAL_H_

void halCreate();
void halDestroy();
void printFont(int x, int y, char *str, int color);
void* allocateMemory(unsigned short size);

#endif