#include <ace/types.h>
#include <ace/utils/extview.h>
#include <ace/generic/screen.h>
#include <ace/managers/copper.h>
#include <ace/managers/viewport/simplebuffer.h>
#include <ace/utils/font.h>
#include <ace/managers/system.h>
#include <ace/managers/joy.h>

#include "../src_common/tracing.h"

static tView *s_pPlayView;
static tVPort *s_pPlayVPort;
static tSimpleBufferManager *s_pPlayBfr;

static tFont *s_pPlayFont;
static tTextBitMap *s_pTextBitMap;
static unsigned long timeCount;
static unsigned short s_uwCopRawOffs;
//static unsigned short s_uwBarY = 160;
static UBYTE s_ubBarHue = 0;
static UBYTE s_isRawMode = 1;

#define TEST_COPPER_COLOR_INSIDE 1


static tCopBlock *s_pBarBlocks[ROWS];
static UWORD pColors[32];

extern unsigned char joyUp, joyDown, joyLeft, joyRight, joyFire;

#define ECS_BPP 4

unsigned char *planes;

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

static unsigned short colorHSV(unsigned char ubH, unsigned char ubS, unsigned char ubV) {
	UBYTE ubRegion, ubRem, p, q, t;

	if (ubS == 0) {
		ubV >>= 4; // 12-bit fit
		return (ubV << 8) | (ubV << 4) | ubV;
	}

	ubRegion = ubH / 43;
	ubRem = (ubH - (ubRegion * 43)) * 6;

	p = (ubV * (255 - ubS)) >> 8;
	q = (ubV * (255 - ((ubS * ubRem) >> 8))) >> 8;
	t = (ubV * (255 - ((ubS * (255 - ubRem)) >> 8))) >> 8;

	ubV >>= 4; p >>= 4; q >>= 4; t >>= 4; // 12-bit fit
	switch (ubRegion) {
		case 0:
			return (ubV << 8) | (t << 4) | p;
		case 1:
			return (q << 8) | (ubV << 4) | p;
		case 2:
			return (p << 8) | (ubV << 4) | t;
		case 3:
			return (p << 8) | (q << 4) | ubV;
		case 4:
			return (t << 8) | (p << 4) | ubV;
		default:
			return (ubV << 8) | (p << 4) | q;
	}
}

void copperTest()
{
	//static BYTE bDir = 1;
	// Regenerate colors for different hue
	++s_ubBarHue;
	//if(s_ubBarHue == 32) s_ubBarHue = 0;
	//UWORD pColors[16];
	// for(UBYTE i = 0; i < 16; ++i) {
	// 	pColors[i] = i*16 + i*8 + i;//colorHSV(s_ubBarHue, 255, i * 17);
	// }
	//for(UBYTE i = 16; i < 32; ++i) {
	//	pColors[i] = colorHSV(s_ubBarHue, 255, (31-i) * 17);
	//}

	// We want to move our copperbar up or down.
	// In RAW mode, you need to take care of doing double WAIT for going past y=255,
	// In BLOCK mode this is done automatically.
	// UWORD uwMaxY = s_isRawMode ? 220 : 280;
	// if(s_uwBarY >= uwMaxY) {
	// 	bDir = -1;
	// 	s_uwBarY = uwMaxY;
	// }
	// if(s_uwBarY <= 30) {
	// 	bDir = 1;
	// 	s_uwBarY = 30;
	// }
	// s_uwBarY += 2 * bDir;

	// ************** RAW MODE **************
	if(s_isRawMode) {
		tCopBfr *pCopBfr = s_pPlayView->pCopList->pBackBfr;
		tCopCmd *pBarCmds = &pCopBfr->pList[s_uwCopRawOffs];
		unsigned short count = 0;

		unsigned char *buffer = (unsigned char*)screenWord;
		buffer++;


		for(unsigned short i = 0; i < ROWS; i++)
		{
			//pBarCmds++;
			count++;
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+2)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+4)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+6)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+8)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+10)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+12)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+14)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+16)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+18)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+20)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+22)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+24)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+26)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+28)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+30)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+32)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+34)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+36)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+38)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+40)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+42)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+44)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+46)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+48)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+50)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+52)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+54)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+56)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+58)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+60)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+62)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+64)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+66)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+68)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+70)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+72)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+74)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+76)];
			pBarCmds[count++].sMove.bfValue = pColors[*(buffer+78)];
			buffer += 80;
			
			//loop copper list 4 times

		}

		// for(UBYTE i = 0; i < 16; ++i) 
		// {
		// 	// Replace WAIT cmd's Y value.
		// 	//pBarCmds[i * 41 + 0].sWait.bfWaitY = s_uwBarY + i;
		// 	for(UBYTE j = 0; j < 40; ++j) 
		// 	{
		// 		pBarCmds[i * 41 + 1 + j].sMove.bfValue = pColors[j];

		// 		//copSetMove(&pBarCmds[i * 41 + 1 + j].sMove, &g_pCustom->color[1], pColors[(j + s_ubBarHue)% 16]);
		// 	}
			
		// }
	}

	else {
		for(UBYTE i = 0; i < ROWS; ++i) {
			for(UBYTE j = 0; j < 40; ++j) {
				s_pPlayView->pCopList->ubStatus |= STATUS_UPDATE;
				s_pBarBlocks[i]->pCmds[j].sMove.bfValue = pColors[(j + s_ubBarHue) % 16];
				// Replace WAIT cmd's Y value.
				//copBlockWait(s_pPlayView->pCopList, s_pBarBlocks[i], 64, 34 + i*2);
				// Replace color value
				//copMove(s_pPlayView->pCopList, s_pBarBlocks[i],&g_pCustom->color[1], pColors[(j + s_ubBarHue) % 16]);
			}
		}
	}
	
}

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

	ULONG ulMode = VIEW_COPLIST_MODE_BLOCK;
	ULONG ulRawSize = 0;
	if(s_isRawMode) {
		ulMode = VIEW_COPLIST_MODE_RAW;
		ulRawSize = (
			simpleBufferGetRawCopperlistInstructionCount(ECS_BPP) +
			ROWS * 41 + // 16 bars, each 40 instructions
			1 + // Final WAIT
			1 // Just to be sure
		);
	}

	// Prepare view & viewport
	s_pPlayView = viewCreate(0,
							 TAG_VIEW_GLOBAL_CLUT, 1,
							TAG_VIEW_COPLIST_MODE, ulMode,         // <-- This is important in RAW mode
							TAG_VIEW_COPLIST_RAW_COUNT, ulRawSize, // <-- This is important in RAW mode
							 //TAG_VIEW_WINDOW_HEIGHT, 20,
							 //TAG_VIEW_WINDOW_START_Y, 100,
							 TAG_DONE);
	s_pPlayVPort = vPortCreate(0,
							   TAG_VPORT_VIEW, s_pPlayView,
							   TAG_VPORT_BPP, ECS_BPP,
							   //TAG_VPORT_WIDTH, 320,
							   //TAG_VPORT_HEIGHT, 20,
							   TAG_DONE);

	s_uwCopRawOffs = 0;
	s_pPlayBfr = simpleBufferCreate(0,
									TAG_SIMPLEBUFFER_VPORT, s_pPlayVPort,
									TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR | BMF_INTERLEAVED,
									TAG_SIMPLEBUFFER_COPLIST_OFFSET, s_uwCopRawOffs, //copper related
									TAG_DONE);

	s_uwCopRawOffs += simpleBufferGetRawCopperlistInstructionCount(ECS_BPP);

//==============================================================================
			// Calculate colors for copper bar.
	// I used HSV - it's a nice color model to get different shades of same color.
	// The V component is brightness - make it go 0..255, 255..0
	
	//for(UBYTE i = 0; i < 16; ++i) {
	//	pColors[i] = colorHSV(s_ubBarHue, 255, i * 17);
	//}
	pColors[0] = 0x0000; // First color is also border color
	pColors[1] = 0x0112; // Gray
	pColors[2] = 0x0223; // Red - not max, a bit dark
	pColors[3] = 0x0434; // Blue - same brightness as red
	pColors[4] = 0x0534; // Blue - same brightness as red
	pColors[5] = 0x0744;
	pColors[6] = 0x0854;
	pColors[7] = 0x0a64;
	pColors[8] = 0x0b74;
	pColors[9] = 0x0d85;
	pColors[10] = 0x0e95;
	pColors[11] = 0x0ea5;
	pColors[12] = 0x0eb6;
	pColors[13] = 0x0fc8;
	pColors[14] = 0x0fda;
	pColors[15] = 0x0fec;
	// for(UBYTE i = 16; i < 32; ++i) {
	// 	pColors[i] = colorHSV(s_ubBarHue, 255, (31-i) * 17);
	// }
  // Create a shaded copperbar. This works by changing color every line.
	// This copperbar is 32px wide with color change in every line, so copper
	// needs to wait for each of 32 lines and change color in each one of them.


	// ************** RAW MODE **************
	if(s_isRawMode) 
	{
		tCopBfr *pCopBfr = s_pPlayView->pCopList->pBackBfr;
		// - Go to position directly after simple buffer's commands.
		tCopCmd *pBarCmds = &pCopBfr->pList[s_uwCopRawOffs];
		// - Write WAIT + MOVE commands for each line.
		for(unsigned char i = 0; i < ROWS; ++i) 
		{
			// copSetWait(&pBarCmds[i * 41 + 0].sWait, 64, 34 + i*4);
			// for(UBYTE j = 0; j < 40; ++j) 
			// {
			// 	copSetMove(&pBarCmds[i * 41 + 1 + j].sMove, &g_pCustom->color[1], pColors[j % 16]);
			// }
		}
		// Copy the same thing to front buffer, so that copperlist has the same
		// structure on both buffers and we can just update parts we need
		// for(unsigned short i = 0; i < pCopBfr->uwAllocSize; ++i) 
		// {
		// 	s_pPlayView->pCopList->pFrontBfr->pList[i].ulCode = (pCopBfr->pList[i].ulCode);
		// }
	}
		else {
		// This is how you do stuff in copperlist's BLOCK mode.
		// - Create a block for each WAIT + N x MOVE instructions,
		// - Set WAIT cmd's x,y in copBlockCreate()
		// for(UBYTE i = 0; i < 16; ++i) {
		// 	s_pBarBlocks[i] = copBlockCreate(s_pPlayView->pCopList, 1, i*8, 0);
		// }

		// - Use copMove() to append MOVE cmds to each block.
		// for(UBYTE i = 0; i < 16; ++i) {
		// 	copMove(
		// 		s_pPlayView->pCopList, s_pBarBlocks[i],
		// 		&g_pCustom->color[1], pColors[i % 16]
		// 	);
		// }

		for(UBYTE i = 0; i < ROWS; ++i) 
		{
			s_pBarBlocks[i] = copBlockCreate(s_pPlayView->pCopList, 40, 64, 34 + i*2);
			for(UBYTE j = 0; j < 40; ++j) 
			{
			copMove(s_pPlayView->pCopList, s_pBarBlocks[i],&g_pCustom->color[1], pColors[j % 16]);
			}
		}
		 

		// Calling copMove() again on same copBlock would append next MOVE
		// instruction drectly after last one.
	}
//==============================================================================

	// Prepare palette
	s_pPlayVPort->pPalette[0] = 0x0000; // First color is also border color
	s_pPlayVPort->pPalette[1] = 0x0112; // Gray
	s_pPlayVPort->pPalette[2] = 0x0223; // Red - not max, a bit dark
	s_pPlayVPort->pPalette[3] = 0x0434; // Blue - same brightness as red
	s_pPlayVPort->pPalette[4] = 0x0534; // Blue - same brightness as red
	s_pPlayVPort->pPalette[5] = 0x0744;
	s_pPlayVPort->pPalette[6] = 0x0854;
	s_pPlayVPort->pPalette[7] = 0x0a64;
	s_pPlayVPort->pPalette[8] = 0x0b74;
	s_pPlayVPort->pPalette[9] = 0x0d85;
	s_pPlayVPort->pPalette[10] = 0x0e95;
	s_pPlayVPort->pPalette[11] = 0x0ea5;
	s_pPlayVPort->pPalette[12] = 0x0eb6;
	s_pPlayVPort->pPalette[13] = 0x0fc8;
	s_pPlayVPort->pPalette[14] = 0x0fda;
	s_pPlayVPort->pPalette[15] = 0x0fec;
	s_pPlayVPort->pPalette[TEST_COPPER_COLOR_INSIDE] = 0xAAA;

	blitRect(
		s_pPlayBfr->pBack, 0,0,
		s_pPlayBfr->uBfrBounds.uwX,
		s_pPlayBfr->uBfrBounds.uwY,
		TEST_COPPER_COLOR_INSIDE
	);

	// Load font
	s_pPlayFont = fontCreate("data/fonts/silkscreen.fnt");
	s_pTextBitMap = fontCreateTextBitMap(32, s_pPlayFont->uwHeight);

	planes =s_pPlayBfr->pBack->Planes[0];

	// Display view with its viewports
	viewLoad(s_pPlayView);
	logBlockEnd("gsPlayCreate");
	systemUnuse();
}
void HalProcess()
{
 //simpleBufferProcess(s_pPlayBfr);
 timerProcess();
 joyProcess();
 //copProcessBlocks();
 //copSwapBuffers() ;
 //vPortWaitForEnd(s_pPlayVPort);
}
void HalDestroy()
{

}
void ProcessInput()
{
	joyUp = joyCheck(JOY1_UP);
	joyDown = joyCheck(JOY1_DOWN);
	joyLeft = joyCheck(JOY1_LEFT);
	joyRight = joyCheck(JOY1_RIGHT);
	joyFire = joyCheck(JOY1_FIRE);

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
		//memcpy(s_pPlayBfr->pBack->Planes[0], planes[0], 8000);
		//memcpy(s_pPlayBfr->pBack->Planes[1], planes[1], 8000);
		//memcpy(s_pPlayBfr->pBack->Planes[2], planes[2], 8000);
		//memcpy(s_pPlayBfr->pBack->Planes[3], planes[3], 8000);

 	//blitCopy(s_pPlanesBitMap, 0, 0,s_pPlayBfr->pBack, 0, 0,320, 32, MINTERM_COOKIE);
}

void timerFormatPrec2(char *szBfr, ULONG ulPrecTime) {
	ULONG ulResult;
	if(ulPrecTime > 0xFFFFFFFF>>2) {
		sprintf(szBfr, ">7min");
		return;
	}
	ulResult = ulPrecTime*4;
	ulResult = ulResult / 10;
	if(ulResult < 1000) {
		sprintf(szBfr, "%3luu", ulResult);
		return;
	}
	ulResult /= 1000;
	if(ulResult < 1000) {
		sprintf(szBfr, "%3lum", ulResult);
		return;
	}
	ulResult /= 1000;
	sprintf(szBfr, "%lus", ulResult);
}

void GetDeltaTime(char str[15])
{
	unsigned long newCount = timerGetPrec();
	timerFormatPrec2( str, timerGetDelta(timeCount,newCount));
	timeCount = newCount;
}

