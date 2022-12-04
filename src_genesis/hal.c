#include <genesis.h>

void halCreate()
{
	
}
printFont(int x, int y, char *str, int color)
{
	VDP_drawText(str, x/8, y/8);
	
}
void* allocateMemory(u16 size)
{
	return MEM_alloc(size);
}