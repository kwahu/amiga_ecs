//#include "tracing.h"
#include <ace/utils/bitmap.h>


unsigned short dither32[16][16][4];
unsigned long dither64[16][16][16][16][4];

void GenDither32()
{
	for(int y = 0; y < 16; ++y)
	{
		for(int x = 0; x < 16; ++x)
		{
			dither32[x][y][0] = 0b11111111 * ((x>>0) & 1) + 0b11111111 * ((y>>0) & 1) * 0x100;
			dither32[x][y][1] = 0b11111111 * ((x>>1) & 1) + 0b11111111 * ((y>>1) & 1) * 0x100;
			dither32[x][y][2] = 0b11111111 * ((x>>2) & 1) + 0b11111111 * ((y>>2) & 1) * 0x100;
			dither32[x][y][3] = 0b11111111 * ((x>>3) & 1) + 0b11111111 * ((y>>3) & 1) * 0x100;
		}
	}
}
void GenDither64()
{
	for(int d = 0; d < 16; ++d)
	{
		for(int c = 0; c < 16; ++c)
		{
			for(int b = 0; b < 16; ++b)
			{
				for(int a = 0; a < 16; ++a)
				{					
					dither64[a][b][c][d][0] = 
						0xf0000000 * ((a>>0) & 1) + 0x0f000000 * ((b>>0) & 1) + 0x00f00000 * ((c>>0) & 1)  + 0x000f0000 * ((d>>0) & 1)
	 					+ 0xf000 * ((a>>1) & 1) + 0x0f00 * ((b>>1) & 1) + 0x00f0 * ((c>>1) & 1)  + 0x000f * ((d>>1) & 1);
					dither64[a][b][c][d][1] = 
						0xf0000000 * ((a>>2) & 1) + 0x0f000000 * ((b>>2) & 1) + 0x00f00000 * ((c>>2) & 1)  + 0x000f0000 * ((d>>2) & 1)
						+ 0xf000 * ((a>>3) & 1) + 0x0f00 * ((b>>3) & 1) + 0x00f0 * ((c>>3) & 1)  + 0x000f * ((d>>3) & 1);
				}
			}
		}
	}
}



void ScreenToPlanes64(unsigned char *buffer, unsigned char *planes[4], unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes[0];
	unsigned int pattern1, pattern2;
	offset += 80 * counter + yoffset * 80;

	for(int y = 32; y > 0; --y)
    {
		for(int x = 0; x < 64; x+=4)
		{
			pattern1 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][0];
			pattern2 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][1];
			*(offset) = (unsigned short)(pattern1>>16);
			*(offset+20) = (unsigned short)(pattern1);
			*(offset+40) = (unsigned short)(pattern2>>16);
			*(offset+60) = (unsigned short)(pattern2);
			offset += 1; //go to next 2 pixels
		}
		offset += 4+60+80+80+80;	//go to next line
    }
}

void ScreenToPlanes64tunel(unsigned char *buffer, unsigned char *planes[4], unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes[0];
	unsigned int pattern1, pattern2;
	offset += 80 * counter + yoffset * 80;

	for(int y = 0; y < 16; ++y)
    {
		for(int x = 0; x < 64; x+=4)
		{
			pattern1 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][0];
			pattern2 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][1];
			*(offset) = (unsigned short)(pattern1>>16);
			*(offset+20) = (unsigned short)(pattern1);
			*(offset+40) = (unsigned short)(pattern2>>16);
			*(offset+60) = (unsigned short)(pattern2);
			offset += 1; //go to next 2 pixels
		}
		offset += 4+60+80+80+80;	//go to next line
    }
	for(int y = 16; y > 0; --y)
    {
		for(int x = 0; x < 64; x+=4)
		{
			pattern1 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][0];
			pattern2 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][1];
			*(offset) = (unsigned short)(pattern1>>16);
			*(offset+20) = (unsigned short)(pattern1);
			*(offset+40) = (unsigned short)(pattern2>>16);
			*(offset+60) = (unsigned short)(pattern2);
			offset += 1; //go to next 2 pixels
		}
		offset += 4+60+80+80+80;	//go to next line
    }

}

void ScreenToPlanes32(unsigned char *screen, unsigned char *planes[4], unsigned char counter)
{
	unsigned short *offset = (unsigned short *) planes[0];

	offset += 80 * counter;

	for(int y = 8; y > 0; --y)
    {
		for(int x = 0; x < 64; x+=4)
		{
			*(offset) = dither32[*(screen+x+y*32)][*(screen+x+1+y*32)][0];
			*(offset+20) = dither32[*(screen+x+y*32)][*(screen+x+1+y*32)][1];
			*(offset+40) = dither32[*(screen+x+y*32)][*(screen+x+1+y*32)][2];
			*(offset+60) = dither32[*(screen+x+y*32)][*(screen+x+1+y*32)][3];
			offset += 1; //go to next 2 pixels
		}
		offset += 4+60+80+80+80;	//go to next line
    }
}