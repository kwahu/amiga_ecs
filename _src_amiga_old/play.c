#include "play.h"
#include "game.h"
#include <ace/utils/extview.h>
#include <ace/generic/screen.h>
#include <ace/managers/viewport/simplebuffer.h>
#include <ace/utils/font.h>
#include <ace/managers/system.h>

static tView *s_pPlayView;
static tVPort *s_pPlayVPort;
static tSimpleBufferManager *s_pPlayBfr;

static tFont *s_pPlayFont;
static tTextBitMap *s_pTextBitMap;

static int yPos, xPos = 8;

void gsPlayCreate(void)
{
	logBlockBegin("gsPlayCreate");
	// Prepare view & viewport
	s_pPlayView = viewCreate(0,
		TAG_VIEW_GLOBAL_CLUT, 1,
		TAG_DONE
	);
	s_pPlayVPort = vPortCreate(0,
		TAG_VPORT_VIEW, s_pPlayView,
		TAG_VPORT_BPP, ECS_BPP,
		TAG_DONE
	);
	s_pPlayBfr = simpleBufferCreate(0,
		TAG_SIMPLEBUFFER_VPORT, s_pPlayVPort,
		TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR,
		TAG_DONE
	);

	// Prepare palette
	s_pPlayVPort->pPalette[0] = 0x000;
	s_pPlayVPort->pPalette[1] = 0xAAA;
	s_pPlayVPort->pPalette[2] = 0x666;
	s_pPlayVPort->pPalette[3] = 0xFFF;
	s_pPlayVPort->pPalette[4] = 0x111;

	// Load font
	s_pPlayFont = fontCreate("data/fonts/silkscreen.fnt");
	s_pTextBitMap = fontCreateTextBitMap(320, s_pPlayFont->uwHeight);

	// Prepare Play lists
	/*s_pPlayList = PlayListCreate(
		160, 100, 10, 2,
		s_pPlayFont, FONT_HCENTER|FONT_COOKIE|FONT_SHADOW,
		1, 2, 3,
		s_pPlayBfr->pBack
	);*/
	//PlayShowMain();

fontFillTextBitMap(s_pPlayFont, s_pTextBitMap, "1234567890");
	

	// Display view with its viewports
	viewLoad(s_pPlayView);
	logBlockEnd("gsPlayCreate");
	systemUnuse();
}
void gsPlayLoop(void)
{
	test_elo();
	
    logBlockBegin("gsPlayLoop");
	
	fontDrawTextBitMap(s_pPlayBfr->pBack, s_pTextBitMap, 128, yPos, 1, FONT_COOKIE|FONT_CENTER);
	
	
	yPos++;
	if(yPos > 190)
	{
		yPos = 0;
	}

	logBlockEnd("gsPlayLoop");
}
void gsPlayDestroy(void)
{
    logBlockBegin("gsPlayDestroy");
}

