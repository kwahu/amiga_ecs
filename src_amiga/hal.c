#include <ace/types.h>
#include <ace/utils/extview.h>
#include <ace/generic/screen.h>
#include <ace/managers/viewport/simplebuffer.h>
#include <ace/utils/font.h>
#include <ace/managers/system.h>
#include <ace/managers/joy.h>

 static tView *s_pPlayView;
 static tVPort *s_pPlayVPort;
 static tSimpleBufferManager *s_pPlayBfr;

 static tFont *s_pPlayFont;
 static tTextBitMap *s_pTextBitMap;
 //static tBitMap *s_pPlanesBitMap;

extern unsigned char joyUp, joyDown, joyLeft, joyRight, joyFire;

 #define ECS_BPP 4

 unsigned char *planes[ECS_BPP];

//-------------------------------------------------------- STACK SMASH DETECTION
#if defined(__GNUC__)
#include <stdint.h>

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn)) void __stack_chk_fail(void)
{
	logWrite("ERR: STACK SMASHED\n");
	while (1)
	{
	}
}
#endif

void HalCreate()
{
	systemCreate();
	logOpen(GENERIC_MAIN_LOG_PATH);
	memCreate();
	timerCreate();
	joyOpen();

	blitManagerCreate();
	copCreate();

	logBlockBegin("gsPlayCreate");
	// Prepare view & viewport
	s_pPlayView = viewCreate(0,
							 TAG_VIEW_GLOBAL_CLUT, 1,
							 //TAG_VIEW_WINDOW_HEIGHT, 20,
							 //TAG_VIEW_WINDOW_START_Y, 100,
							 TAG_DONE);
	s_pPlayVPort = vPortCreate(0,
							   TAG_VPORT_VIEW, s_pPlayView,
							   TAG_VPORT_BPP, ECS_BPP,
							   //TAG_VPORT_WIDTH, 320,
							   //TAG_VPORT_HEIGHT, 20,
							   TAG_DONE);
	s_pPlayBfr = simpleBufferCreate(0,
									TAG_SIMPLEBUFFER_VPORT, s_pPlayVPort,
									TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR | BMF_INTERLEAVED,
									TAG_DONE);

	// Prepare palette
	s_pPlayVPort->pPalette[0] = 0x0000; // First color is also border color
	s_pPlayVPort->pPalette[1] = 0x0111; // Gray
	s_pPlayVPort->pPalette[2] = 0x0222; // Red - not max, a bit dark
	s_pPlayVPort->pPalette[3] = 0x0333; // Blue - same brightness as red
	s_pPlayVPort->pPalette[4] = 0x0444; // Blue - same brightness as red
	s_pPlayVPort->pPalette[5] = 0x0555;
	s_pPlayVPort->pPalette[6] = 0x0666;
	s_pPlayVPort->pPalette[7] = 0x0777;
	s_pPlayVPort->pPalette[8] = 0x0888;
	s_pPlayVPort->pPalette[9] = 0x0999;
	s_pPlayVPort->pPalette[10] = 0x0aaa;
	s_pPlayVPort->pPalette[11] = 0x0bbb;
	s_pPlayVPort->pPalette[12] = 0x0ccc;
	s_pPlayVPort->pPalette[13] = 0x0ddd;
	s_pPlayVPort->pPalette[14] = 0x0eee;
	s_pPlayVPort->pPalette[15] = 0x0fff;

	// Load font
	s_pPlayFont = fontCreate("data/fonts/silkscreen.fnt");
	s_pTextBitMap = fontCreateTextBitMap(160, s_pPlayFont->uwHeight);

	//s_pPlanesBitMap = bitmapCreate(320, 200, ECS_BPP, BMF_FASTMEM);

	planes[0] = s_pPlayBfr->pBack->Planes[0];
	planes[1] = s_pPlayBfr->pBack->Planes[1];
	planes[2] = s_pPlayBfr->pBack->Planes[2];
	planes[3] = s_pPlayBfr->pBack->Planes[3];

	// Display view with its viewports
	viewLoad(s_pPlayView);
	logBlockEnd("gsPlayCreate");
	systemUnuse();
}
void HalProcess()
{
 simpleBufferProcess(s_pPlayBfr);
 timerProcess();
 joyProcess();
 vPortWaitForEnd(s_pPlayVPort);
}
void HalDestroy()
{

}
void ProcessInput()
{
	joyUp = joyCheck(JOY1_UP);
	joyDown = joyCheck(JOY1_DOWN);
	joyLeft = joyUse(JOY1_LEFT);
	joyRight = joyUse(JOY1_RIGHT);
	joyFire = joyUse(JOY1_FIRE);

	//if(keyUse(KEY_UP) || joyUse(JOY1_UP)) {

}
void printFont(int x, int y, char *str, int color)
{
	fontFillTextBitMap(s_pPlayFont, s_pTextBitMap, str);
	fontDrawTextBitMap(s_pPlayBfr->pBack, s_pTextBitMap, x, y, color, FONT_COOKIE | FONT_CENTER);
}
void *allocateMemory(UWORD size)
{
	return memAllocFast(size);
}
void MovePlanesToChip()
{


//CopyMemQuick
		//memcpy(s_pPlayBfr->pBack->Planes[0], planes[0], 8000);
		//memcpy(s_pPlayBfr->pBack->Planes[1], planes[1], 8000);
		//memcpy(s_pPlayBfr->pBack->Planes[2], planes[2], 8000);
		//memcpy(s_pPlayBfr->pBack->Planes[3], planes[3], 8000);

 	//blitCopy(s_pPlanesBitMap, 0, 0,s_pPlayBfr->pBack, 0, 0,320, 20, MINTERM_COOKIE);
	
}