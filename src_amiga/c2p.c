//#include "tracing.h"
#include <ace/utils/bitmap.h>






void ScreenToPlanes(unsigned char *screen, unsigned char *planes[4], unsigned char counter)
{
	//unsigned short int offset = 0;
	//unsigned short int position = 0;
	unsigned char color = counter;

	unsigned short *offset = (unsigned short *) planes[0];

	for(int y = 0; y < 64; y++)
    {
		for(int x = 0; x < 32; x+=2)
		{
			//write 16 pixels at once across 4 planes
			*(offset) = 0b11111111 * ((*(screen+x+y*32)>>0) & 1) + 0b11111111 * ((*(screen+x+1+y*32)>>0) & 1) * 0x100;
			*(offset+20) = 0b11111111 * ((*(screen+x+y*32)>>1) & 1) + 0b11111111 * ((*(screen+x+1+y*32)>>1) & 1) * 0x100;
			*(offset+40) = 0b11111111 * ((*(screen+x+y*32)>>2) & 1) + 0b11111111 * ((*(screen+x+1+y*32)>>2) & 1) * 0x100;
			*(offset+60) = 0b11111111 * ((*(screen+x+y*32)>>3) & 1) + 0b11111111 * ((*(screen+x+1+y*32)>>3) & 1) * 0x100;

			//color+=2;
			offset += 1; //go to next 2 pixels
		}
		offset += 60+4;	//go to next line
    }
}