#include <ace/types.h>
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

#define ECS_BPP 4

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

void halCreate()
{
	systemCreate();
	logOpen(GENERIC_MAIN_LOG_PATH);
	memCreate();
	timerCreate();

	blitManagerCreate();
	copCreate();

	logBlockBegin("gsPlayCreate");
	// Prepare view & viewport
	s_pPlayView = viewCreate(0,
							 TAG_VIEW_GLOBAL_CLUT, 1,
							 TAG_DONE);
	s_pPlayVPort = vPortCreate(0,
							   TAG_VPORT_VIEW, s_pPlayView,
							   TAG_VPORT_BPP, ECS_BPP,
							   TAG_DONE);
	s_pPlayBfr = simpleBufferCreate(0,
									TAG_SIMPLEBUFFER_VPORT, s_pPlayVPort,
									TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR,
									TAG_DONE);

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
	// PlayShowMain();

	// Display view with its viewports
	viewLoad(s_pPlayView);
	logBlockEnd("gsPlayCreate");
	systemUnuse();
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