//#include "tracing.h"
#include <ace/utils/bitmap.h>


//unsigned short dither32[16][16][4];
unsigned short dither64[32][32][4];

// void GenDither32()
// {
// 	for(int y = 0; y < 16; ++y)
// 	{
// 		for(int x = 0; x < 16; ++x)
// 		{
// 			dither32[x][y][0] = 0b11111111 * ((x>>0) & 1) + 0b11111111 * ((y>>0) & 1) * 0x100;
// 			dither32[x][y][1] = 0b11111111 * ((x>>1) & 1) + 0b11111111 * ((y>>1) & 1) * 0x100;
// 			dither32[x][y][2] = 0b11111111 * ((x>>2) & 1) + 0b11111111 * ((y>>2) & 1) * 0x100;
// 			dither32[x][y][3] = 0b11111111 * ((x>>3) & 1) + 0b11111111 * ((y>>3) & 1) * 0x100;
// 		}
// 	}
// }
void GenDither64()
{
	for(int b = 0; b < 32; ++b)
	{
		for(int a = 0; a < 32; ++a)
		{			
			if(a % 2 || a == 0)
			{
				dither64[a][b][0] = 0xf000 * (((a/2)>>0) & 1)  + 0xf0 * (((a/2)>>2) & 1);
				dither64[a][b][1] = 0xf000 * (((a/2)>>1) & 1)  + 0xf0 * (((a/2)>>3) & 1);
			}
			else
			{
				dither64[a][b][0] = 0xa000 * (((a/2)>>0) & 1) + 0xa0 * (((a/2)>>2) & 1);
				dither64[a][b][1] = 0xa000 * (((a/2)>>1) & 1) + 0xa0 * (((a/2)>>3) & 1);
				dither64[a][b][0] += 0x5000 * (((a/2-1)>>0) & 1) + 0x50 * (((a/2-1)>>2) & 1);
				dither64[a][b][1] += 0x5000 * (((a/2-1)>>1) & 1) + 0x50 * (((a/2-1)>>3) & 1);
			}
			if(b % 2 || b == 0)
			{
				dither64[a][b][0] += 0x0f00 * (((b/2)>>0) & 1) + 0x0f * (((b/2)>>2) & 1);
				dither64[a][b][1] += 0x0f00 * (((b/2)>>1) & 1)  + 0x0f * (((b/2)>>3) & 1);
			}
			else
			{
				dither64[a][b][0] += 0x0a00 * (((b/2)>>0) & 1) + 0x0a * (((b/2)>>2) & 1);
				dither64[a][b][1] += 0x0a00 * (((b/2)>>1) & 1) + 0x0a * (((b/2)>>3) & 1);
				dither64[a][b][0] += 0x0500 * (((b/2-1)>>0) & 1) + 0x05 * (((b/2-1)>>2) & 1);
				dither64[a][b][1] += 0x0500 * (((b/2-1)>>1) & 1) + 0x05 * (((b/2-1)>>3) & 1);

			}
		}
	}
}



void ScreenToPlanes64(unsigned char *buffer, unsigned char *planes[4], unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes[0];
	offset += 80 * counter + yoffset * 80;

	unsigned short value1, value2, value3, value4;

	for(int y = 32; y > 0; --y)
    {
		for(int x = 0; x < 64; x+=4)
		{
			value1 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][0];
			value2 = dither64[*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][0];
			value3 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][1];
			value4 = dither64[*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][1];

			*(offset) = 	(value1 & 0xff00) + value2 / 256;
			*(offset+20) = 	(value3 & 0xff00) + value4 / 256;
			*(offset+40) = 	(value1 & 0xff) * 256 + (value2 & 0xff);
			*(offset+60) = 	(value3 & 0xff) * 256 + (value4 & 0xff);
			offset += 1; //go to next 2 pixels
		}
		offset += 4+60+80+80+80;	//go to next line
    }
}

// void ScreenToPlanes64tunel(unsigned char *buffer, unsigned char *planes[4], unsigned char counter, unsigned char yoffset)
// {
// 	unsigned short *offset = (unsigned short *) planes[0];
// 	unsigned int pattern1, pattern2;
// 	offset += 80 * counter + yoffset * 80;

// 	for(int y = 0; y < 16; ++y)
//     {
// 		for(int x = 0; x < 64; x+=4)
// 		{
// 			pattern1 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][0];
// 			pattern2 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][1];
// 			*(offset) = (unsigned short)(pattern1>>16);
// 			*(offset+20) = (unsigned short)(pattern1);
// 			*(offset+40) = (unsigned short)(pattern2>>16);
// 			*(offset+60) = (unsigned short)(pattern2);
// 			offset += 1; //go to next 2 pixels
// 		}
// 		offset += 4+60+80+80+80;	//go to next line
//     }
// 	for(int y = 16; y > 0; --y)
//     {
// 		for(int x = 0; x < 64; x+=4)
// 		{
// 			pattern1 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][0];
// 			pattern2 = dither64[*(buffer+x+y*64)][*(buffer+x+1+y*64)][*(buffer+x+2+y*64)][*(buffer+x+3+y*64)][1];
// 			*(offset) = (unsigned short)(pattern1>>16);
// 			*(offset+20) = (unsigned short)(pattern1);
// 			*(offset+40) = (unsigned short)(pattern2>>16);
// 			*(offset+60) = (unsigned short)(pattern2);
// 			offset += 1; //go to next 2 pixels
// 		}
// 		offset += 4+60+80+80+80;	//go to next line
//     }

// }

// void ScreenToPlanes32(unsigned char *screen, unsigned char *planes[4], unsigned char counter)
// {
// 	unsigned short *offset = (unsigned short *) planes[0];

// 	offset += 80 * counter;

// 	for(int y = 8; y > 0; --y)
//     {
// 		for(int x = 0; x < 64; x+=4)
// 		{
// 			*(offset) = dither32[*(screen+x+y*32)][*(screen+x+1+y*32)][0];
// 			*(offset+20) = dither32[*(screen+x+y*32)][*(screen+x+1+y*32)][1];
// 			*(offset+40) = dither32[*(screen+x+y*32)][*(screen+x+1+y*32)][2];
// 			*(offset+60) = dither32[*(screen+x+y*32)][*(screen+x+1+y*32)][3];
// 			offset += 1; //go to next 2 pixels
// 		}
// 		offset += 4+60+80+80+80;	//go to next line
//     }
// }