#include <exec/types.h>
#include <hardware/custom.h>

/* 
 * Copper Chunky example for Amiga 500 
 *
 * This program will fill the screen with vertical stripes of
 * different colors.
 */

void SetCopper()
{
	struct Custom *custom = (struct Custom *) 0xdff000;

	/* 
	 * Set up copper list. 
	 * The list consists of a single instruction which will 
	 * be executed continuously. The instruction is to 
	 * set the background color to $0000 and the border 
	 * color to $FFFF.
	 */
	custom->cop1lc = 0x81808000;
	custom->cop2lc = 0x81808FFF;

	/* 
	 * Set up display.
	 * Set up the display to use 16 colors with 640x512 resolution.
	 */
	custom->dmacon = 0x8400;
	custom->bplcon0 = 0x220;
	custom->bplcon2 = 0x1fc0;
	custom->bplcon3 = 0x0100;
	custom->diwstrt = 0x2c81;
	custom->diwstop = 0x2cc1;
	custom->ddfstrt = 0x0038;
	custom->ddfstop = 0x00d0;
	custom->htotal = 0x0140; //320
	custom->hsstrt = 0x0060;
	custom->hsstop = 0x00b0; //176
	custom->vtotal = 0x02b0; //688
	custom->vsstrt = 0x0028;
	custom->vsstop = 0x0280; //640
	custom->beamcon0 = 0x00;

	/* 
	 * Set up color palette.
	 * We set up a simple color palette with 16 colors.
	 */
	custom->color[0] = 0x0000;
	custom->color[1] = 0x0f00;
	custom->color[2] = 0x00f0;
	custom->color[3] = 0x0ff0;
	custom->color[4] = 0x000f;
	custom->color[5] = 0x0f0f;
	custom->color[6] = 0x00ff;
	custom->color[7] = 0x0fff;
	custom->color[8] = 0x4444;
	custom->color[9] = 0x4f44;
	custom->color[10] = 0x44f4;
	custom->color[11] = 0x4ff4;
	custom->color[12] = 0x444f;
	custom->color[13] = 0x4f4f;
	custom->color[14] = 0x44ff;
	custom->color[15] = 0x4fff;

	/* 
	 * Set up bitplane pointers.
	 * We set up the 4 bitplane pointers to point to a 
	 * single block of memory. 
	 */
	custom->bplpt[0] = 0x880000;
	custom->bplpt[1] = 0x880000;
	custom->bplpt[2] = 0x880000;
	custom->bplpt[3] = 0x880000;

	/* 
	 * Enable Copper and Bitplanes.
	 * We set the DMA Control register to enable the Copper 
	 * and the 4 Bitplanes.
	 */
	custom->dmacon = 0x9F00;


}