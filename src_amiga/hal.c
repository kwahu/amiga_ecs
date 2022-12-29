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
static unsigned char s_isCopperChunky = 0;

#define TEST_COPPER_COLOR_INSIDE 1


//static tCopBlock *s_pBarBlocks[ROWS];
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

void SetCopperChunky(unsigned char value)
{
	s_isCopperChunky = value;
}
unsigned char GetCopperChunky()
{
	return s_isCopperChunky;
}

void copperTest()
{
	++s_ubBarHue;

	if(s_isCopperChunky) {
		tCopBfr *pCopBfr = s_pPlayView->pCopList->pFrontBfr;
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
			pBarCmds[count++].sMove.bfValue = pColors[0];
			// count++;
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+2)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+4)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+6)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+8)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+10)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+12)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+14)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+16)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+18)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+20)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+22)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+24)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+26)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+28)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+30)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+32)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+34)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+36)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+38)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+40)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+42)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+44)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+46)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+48)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+50)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+52)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+54)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+56)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+58)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+60)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+62)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+64)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+66)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+68)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+70)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+72)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+74)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+76)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+78)];
			// pBarCmds[count++].sMove.bfValue = pColors[0];
			// 			count++;
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+2)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+4)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+6)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+8)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+10)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+12)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+14)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+16)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+18)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+20)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+22)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+24)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+26)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+28)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+30)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+32)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+34)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+36)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+38)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+40)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+42)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+44)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+46)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+48)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+50)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+52)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+54)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+56)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+58)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+60)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+62)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+64)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+66)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+68)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+70)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+72)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+74)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+76)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+78)];
			// pBarCmds[count++].sMove.bfValue = pColors[0];
			// 			count++;
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+2)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+4)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+6)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+8)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+10)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+12)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+14)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+16)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+18)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+20)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+22)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+24)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+26)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+28)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+30)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+32)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+34)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+36)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+38)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+40)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+42)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+44)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+46)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+48)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+50)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+52)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+54)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+56)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+58)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+60)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+62)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+64)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+66)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+68)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+70)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+72)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+74)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+76)];
			// pBarCmds[count++].sMove.bfValue = pColors[*(buffer+78)];
			// pBarCmds[count++].sMove.bfValue = pColors[0];
			buffer += 80;
			
			//loop copper list 4 times

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

	if(s_isCopperChunky) {
		ulMode = VIEW_COPLIST_MODE_RAW;
		ulRawSize = (
			simpleBufferGetRawCopperlistInstructionCount(ECS_BPP) +
			ROWS * 42 + // 16 bars, each 40 instructions
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

	if(s_isCopperChunky) 
	s_pPlayBfr = simpleBufferCreate(0,
									TAG_SIMPLEBUFFER_VPORT, s_pPlayVPort,
									TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR | BMF_INTERLEAVED,
									TAG_SIMPLEBUFFER_COPLIST_OFFSET, s_uwCopRawOffs, //copper related
									TAG_DONE);
	else
	s_pPlayBfr = simpleBufferCreate(0,
									TAG_SIMPLEBUFFER_VPORT, s_pPlayVPort,
									TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR | BMF_INTERLEAVED,
									TAG_DONE);

	



	// ************** RAW MODE **************
	if(s_isCopperChunky) 
	{
		//fill the area with the copper chunky color
		blitRect(s_pPlayBfr->pBack, 0,0,s_pPlayBfr->uBfrBounds.uwX,s_pPlayBfr->uBfrBounds.uwY,TEST_COPPER_COLOR_INSIDE);

		s_uwCopRawOffs += simpleBufferGetRawCopperlistInstructionCount(ECS_BPP);

		pColors[0] = 0x0000;pColors[1] = 0x0111;
		pColors[2] = 0x0112; pColors[3] = 0x0222; 
		pColors[4] = 0x0223; pColors[5] = 0x0323; 
		pColors[6] = 0x0434; pColors[7] = 0x0544; 
		pColors[8] = 0x0534; pColors[9] = 0x0644; 
		pColors[10] = 0x0744;pColors[11] = 0x0754;
		pColors[12] = 0x0854;pColors[13] = 0x0954;
		pColors[14] = 0x0a64;pColors[15] = 0x0b64;
		pColors[16] = 0x0b74;pColors[17] = 0x0c84;
		pColors[18] = 0x0d85;pColors[19] = 0x0e85;
		pColors[20] = 0x0e95;pColors[21] = 0x0ea5;
		pColors[22] = 0x0eb5;pColors[23] = 0x0eb6;
		pColors[24] = 0x0fb6;pColors[25] = 0x0fb7;
		pColors[26] = 0x0fc8;pColors[27] = 0x0fc9;
		pColors[28] = 0x0fda;pColors[29] = 0x0fdb;
		pColors[30] = 0x0fec;pColors[31] = 0x0fed;

		
		
	

		tCopBfr *pCopBfr = s_pPlayView->pCopList->pBackBfr;
		// - Go to position directly after simple buffer's commands.
		tCopCmd *pBarCmds = &pCopBfr->pList[s_uwCopRawOffs];


		// // Higher word
		// unsigned bfWaitY        :8; /// Y position
		// unsigned bfWaitX        :7; /// X position
		// unsigned bfIsWait       :1; /// Always set to 1
		// // Lower word
		// unsigned bfBlitterIgnore:1; /// If set to 0, waits for pos and blit finish
		// unsigned bfVE           :7; /// Y compare enable bits
		// unsigned bfHE           :7; /// X compare enable bits
		// unsigned bfIsSkip       :1; /// Set to 1 for SKIP, 0 for WAIT

		for(unsigned char i = 0; i < ROWS; ++i) 
		{
			//0
			copSetWait(&pBarCmds[i * 42 + 0].sWait, 64, 34 + i);
			//1-41
			for(UBYTE j = 0; j < 40; ++j) 
			{
				copSetMove(&pBarCmds[i * 42 + 1 + j].sMove, &g_pCustom->color[1], pColors[j % 32]);
			}
			//42
			copSetMove(&pBarCmds[i * 42 + 41].sMove, &g_pCustom->color[1], pColors[0]);
			//43
			//copSetWait(&pBarCmds[i * 42 + 0].sWait.bfIsSkip = 1, 0, 34 + i);

			
		}



		// Copy the same thing to front buffer, so that copperlist has the same
		// structure on both buffers and we can just update parts we need
		// for(unsigned short i = 0; i < pCopBfr->uwAllocSize; ++i) 
		// {
		// 	s_pPlayView->pCopList->pFrontBfr->pList[i].ulCode = (pCopBfr->pList[i].ulCode);
		// }
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
	//s_pPlayVPort->pPalette[TEST_COPPER_COLOR_INSIDE] = 0xAAA;

		

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

	if(s_isCopperChunky)
	{
		tCopList *pCopList;
		pCopList = g_sCopManager.pCopList;
		g_pCustom->cop1lc = (ULONG)((void *)pCopList->pFrontBfr->pList);
	}
	
	//copProcessBlocks();
	//if(s_isCopperChunky)
 	//	copSwapBuffers() ;
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

