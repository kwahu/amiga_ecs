//#include "tracing.h"
#include <ace/utils/bitmap.h>
#include "../src_common/tracing.h"

//unsigned short ditherWord[32][32][2];		//8kb
unsigned char dither4x4[32][32][4];		//4kb
unsigned short dither4x4shifted[32][32][4];	//8kb

unsigned char dither2x2[32][32][32][32][4];

// void GenDitherWord()
// {
// 	for(int b = 0; b < 32; ++b)
// 	{
// 		for(int a = 0; a < 32; ++a)
// 		{			
// 			if(a % 2 || a == 0)
// 			{
// 				ditherWord[a][b][0] = 0xf000 * (((a/2)>>0) & 1)  + 0xf0 * (((a/2)>>2) & 1);
// 				ditherWord[a][b][1] = 0xf000 * (((a/2)>>1) & 1)  + 0xf0 * (((a/2)>>3) & 1);
// 			}
// 			else
// 			{
// 				ditherWord[a][b][0] = 0xa000 * (((a/2)>>0) & 1) + 0xa0 * (((a/2)>>2) & 1);
// 				ditherWord[a][b][1] = 0xa000 * (((a/2)>>1) & 1) + 0xa0 * (((a/2)>>3) & 1);
// 				ditherWord[a][b][0] += 0x5000 * (((a/2-1)>>0) & 1) + 0x50 * (((a/2-1)>>2) & 1);
// 				ditherWord[a][b][1] += 0x5000 * (((a/2-1)>>1) & 1) + 0x50 * (((a/2-1)>>3) & 1);
// 			}
// 			if(b % 2 || b == 0)
// 			{
// 				ditherWord[a][b][0] += 0x0f00 * (((b/2)>>0) & 1) + 0x0f * (((b/2)>>2) & 1);
// 				ditherWord[a][b][1] += 0x0f00 * (((b/2)>>1) & 1)  + 0x0f * (((b/2)>>3) & 1);
// 			}
// 			else
// 			{
// 				ditherWord[a][b][0] += 0x0a00 * (((b/2)>>0) & 1) + 0x0a * (((b/2)>>2) & 1);
// 				ditherWord[a][b][1] += 0x0a00 * (((b/2)>>1) & 1) + 0x0a * (((b/2)>>3) & 1);
// 				ditherWord[a][b][0] += 0x0500 * (((b/2-1)>>0) & 1) + 0x05 * (((b/2-1)>>2) & 1);
// 				ditherWord[a][b][1] += 0x0500 * (((b/2-1)>>1) & 1) + 0x05 * (((b/2-1)>>3) & 1);
// 			}
// 		}
// 	}
// }

//make 4 loops to cover all 4 entry values
void GenDither2x2()
{
	for(int d = 0; d < 32; ++d)
	{
		for(int c = 0; c < 32; ++c)
		{			
			for(int b = 0; b < 32; ++b)
			{
				for(int a = 0; a < 32; ++a)
				{
					if(a % 2 || a == 0)
					{
						dither2x2[a][b][c][d][0] = 0b11000000 * (((a/2)>>0) & 1);
						dither2x2[a][b][c][d][1] = 0b11000000 * (((a/2)>>1) & 1);
						dither2x2[a][b][c][d][2] = 0b11000000 * (((a/2)>>2) & 1);
						dither2x2[a][b][c][d][3] = 0b11000000 * (((a/2)>>3) & 1);
					}
					else
					{
						dither2x2[a][b][c][d][0] = 0b10000000 * (((a/2)>>0) & 1);
						dither2x2[a][b][c][d][1] = 0b10000000 * (((a/2)>>1) & 1);
						dither2x2[a][b][c][d][2] = 0b10000000 * (((a/2)>>2) & 1);
						dither2x2[a][b][c][d][3] = 0b10000000 * (((a/2)>>3) & 1);
						dither2x2[a][b][c][d][0] += 0b01000000 * (((a/2-1)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b01000000 * (((a/2-1)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b01000000 * (((a/2-1)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b01000000 * (((a/2-1)>>3) & 1);
					}
					if(b % 2 || b == 0)
					{
						dither2x2[a][b][c][d][0] += 0b00110000 * (((b/2)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b00110000 * (((b/2)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b00110000 * (((b/2)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b00110000 * (((b/2)>>3) & 1);
					}
					else
					{
						dither2x2[a][b][c][d][0] += 0b00100000 * (((b/2)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b00100000 * (((b/2)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b00100000 * (((b/2)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b00100000 * (((b/2)>>3) & 1);
						dither2x2[a][b][c][d][0] += 0b00010000 * (((b/2-1)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b00010000 * (((b/2-1)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b00010000 * (((b/2-1)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b00010000 * (((b/2-1)>>3) & 1);
					}
					if(c % 2 || c == 0)
					{
						dither2x2[a][b][c][d][0] += 0b00001100 * (((c/2)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b00001100 * (((c/2)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b00001100 * (((c/2)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b00001100 * (((c/2)>>3) & 1);
					}
					else
					{
						dither2x2[a][b][c][d][0] += 0b00001000 * (((c/2)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b00001000 * (((c/2)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b00001000 * (((c/2)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b00001000 * (((c/2)>>3) & 1);
						dither2x2[a][b][c][d][0] += 0b00000100 * (((c/2-1)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b00000100 * (((c/2-1)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b00000100 * (((c/2-1)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b00000100 * (((c/2-1)>>3) & 1);
					}
					if(d % 2 || d == 0)
					{
						dither2x2[a][b][c][d][0] += 0b00000011 * (((d/2)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b00000011 * (((d/2)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b00000011 * (((d/2)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b00000011 * (((d/2)>>3) & 1);
					}
					else
					{
						dither2x2[a][b][c][d][0] += 0b00000010 * (((d/2)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b00000010 * (((d/2)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b00000010 * (((d/2)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b00000010 * (((d/2)>>3) & 1);
						dither2x2[a][b][c][d][0] += 0b00000001 * (((d/2-1)>>0) & 1);
						dither2x2[a][b][c][d][1] += 0b00000001 * (((d/2-1)>>1) & 1);
						dither2x2[a][b][c][d][2] += 0b00000001 * (((d/2-1)>>2) & 1);
						dither2x2[a][b][c][d][3] += 0b00000001 * (((d/2-1)>>3) & 1);
					}
				}
			}
		}
	}
}

void GenDither4x4()
{
	for(int b = 0; b < 32; ++b)
	{
		for(int a = 0; a < 32; ++a)
		{			
			if(a % 2 || a == 0)
			{
				dither4x4[a][b][0] = 0xf0 * (((a/2)>>0) & 1);
				dither4x4[a][b][1] = 0xf0 * (((a/2)>>1) & 1);
				dither4x4[a][b][2] = 0xf0 * (((a/2)>>2) & 1);
				dither4x4[a][b][3] = 0xf0 * (((a/2)>>3) & 1);
			}
			else
			{
				dither4x4[a][b][0] = 0xa0 * (((a/2)>>0) & 1);
				dither4x4[a][b][1] = 0xa0 * (((a/2)>>1) & 1);
				dither4x4[a][b][2] = 0xa0 * (((a/2)>>2) & 1);
				dither4x4[a][b][3] = 0xa0 * (((a/2)>>3) & 1);
				dither4x4[a][b][0] += 0x50 * (((a/2-1)>>0) & 1); 
				dither4x4[a][b][1] += 0x50 * (((a/2-1)>>1) & 1);
				dither4x4[a][b][2] += 0x50 * (((a/2-1)>>2) & 1);
				dither4x4[a][b][3] += 0x50 * (((a/2-1)>>3) & 1);
			}
			if(b % 2 || b == 0)
			{
				dither4x4[a][b][0] += 0x0f * (((b/2)>>0) & 1);
				dither4x4[a][b][1] += 0x0f * (((b/2)>>1) & 1);
				dither4x4[a][b][2] += 0x0f * (((b/2)>>2) & 1);
				dither4x4[a][b][3] += 0x0f * (((b/2)>>3) & 1);
			}
			else
			{
				dither4x4[a][b][0] += 0x0a * (((b/2)>>0) & 1);
				dither4x4[a][b][1] += 0x0a * (((b/2)>>1) & 1);
				dither4x4[a][b][2] += 0x0a * (((b/2)>>2) & 1);
				dither4x4[a][b][3] += 0x0a * (((b/2)>>3) & 1);
				dither4x4[a][b][0] += 0x05 * (((b/2-1)>>0) & 1);
				dither4x4[a][b][1] += 0x05 * (((b/2-1)>>1) & 1);
				dither4x4[a][b][2] += 0x05 * (((b/2-1)>>2) & 1);
				dither4x4[a][b][3] += 0x05 * (((b/2-1)>>3) & 1);
			}
		}
	}
}
void GenDither4x4Shifted()
{
	for(int b = 0; b < 32; ++b)
	{
		for(int a = 0; a < 32; ++a)
		{			
			if(a % 2 || a == 0)
			{
				dither4x4shifted[a][b][0] = 0xf000 * (((a/2)>>0) & 1);
				dither4x4shifted[a][b][1] = 0xf000 * (((a/2)>>1) & 1);
				dither4x4shifted[a][b][2] = 0xf000 * (((a/2)>>2) & 1);
				dither4x4shifted[a][b][3] = 0xf000 * (((a/2)>>3) & 1);
			}
			else
			{
				dither4x4shifted[a][b][0] = 0xa000 * (((a/2)>>0) & 1);
				dither4x4shifted[a][b][1] = 0xa000 * (((a/2)>>1) & 1);
				dither4x4shifted[a][b][2] = 0xa000 * (((a/2)>>2) & 1);
				dither4x4shifted[a][b][3] = 0xa000 * (((a/2)>>3) & 1);
				dither4x4shifted[a][b][0] += 0x5000 * (((a/2-1)>>0) & 1); 
				dither4x4shifted[a][b][1] += 0x5000 * (((a/2-1)>>1) & 1);
				dither4x4shifted[a][b][2] += 0x5000 * (((a/2-1)>>2) & 1);
				dither4x4shifted[a][b][3] += 0x5000 * (((a/2-1)>>3) & 1);
			}
			if(b % 2 || b == 0)
			{
				dither4x4shifted[a][b][0] += 0x0f00 * (((b/2)>>0) & 1);
				dither4x4shifted[a][b][1] += 0x0f00 * (((b/2)>>1) & 1);
				dither4x4shifted[a][b][2] += 0x0f00 * (((b/2)>>2) & 1);
				dither4x4shifted[a][b][3] += 0x0f00 * (((b/2)>>3) & 1);
			}
			else
			{
				dither4x4shifted[a][b][0] += 0x0a00 * (((b/2)>>0) & 1);
				dither4x4shifted[a][b][1] += 0x0a00 * (((b/2)>>1) & 1);
				dither4x4shifted[a][b][2] += 0x0a00 * (((b/2)>>2) & 1);
				dither4x4shifted[a][b][3] += 0x0a00 * (((b/2)>>3) & 1);
				dither4x4shifted[a][b][0] += 0x0500 * (((b/2-1)>>0) & 1);
				dither4x4shifted[a][b][1] += 0x0500 * (((b/2-1)>>1) & 1);
				dither4x4shifted[a][b][2] += 0x0500 * (((b/2-1)>>2) & 1);
				dither4x4shifted[a][b][3] += 0x0500 * (((b/2-1)>>3) & 1);
			}
		}
	}
}
#pragma GCC push_options
#pragma GCC optimize ("peel-loops")
void ScreenToPlanes4x4(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes + 80 * counter + yoffset * 80;

	unsigned short value1, value2, value3, value4;
	unsigned char value5, value6, value7, value8;

	buffer++;
	for(unsigned char y = 0; y < ROWS; y++)
    {

		for(unsigned short i = 0; i < (COLUMNS/4); i++)
		{
			value1 = dither4x4shifted[*(buffer)][*(buffer+2)][0];
			value2 = dither4x4shifted[*(buffer)][*(buffer+2)][1];
			value3 = dither4x4shifted[*(buffer)][*(buffer+2)][2];
			value4 = dither4x4shifted[*(buffer)][*(buffer+2)][3];
			buffer += 4;
			value5 = dither4x4[*(buffer)][*(buffer+2)][0];
			value6 = dither4x4[*(buffer)][*(buffer+2)][1];
			value7 = dither4x4[*(buffer)][*(buffer+2)][2];
			value8 = dither4x4[*(buffer)][*(buffer+2)][3];
			buffer += 4;

			*(offset) = 	value1  + value5;
			*(offset+40) = 	value2  + value6;
			*(offset+20) = 	value3  + value7;
			*(offset+60) = 	value4  + value8;
			offset += 1;
		}
		offset += 320 - COLUMNS/4;
    }
}

void ScreenToPlanes2x2(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes + 80 * counter + yoffset * 80;

	unsigned char value1, value2, value3, value4;
	unsigned char value5, value6, value7, value8;

	buffer++;
	for(unsigned char y = 0; y < ROWS; y++)
    {

		for(unsigned short i = 0; i < (COLUMNS/8); i++)
		{
			value1 = dither2x2[*(buffer)][*(buffer+2)][*(buffer+4)][*(buffer+6)][0];
			value2 = dither2x2[*(buffer)][*(buffer+2)][*(buffer+4)][*(buffer+6)][1];
			value3 = dither2x2[*(buffer)][*(buffer+2)][*(buffer+4)][*(buffer+6)][2];
			value4 = dither2x2[*(buffer)][*(buffer+2)][*(buffer+4)][*(buffer+6)][3];
			buffer += 8;
			value5 = dither2x2[*(buffer)][*(buffer+2)][*(buffer+4)][*(buffer+6)][0];
			value6 = dither2x2[*(buffer)][*(buffer+2)][*(buffer+4)][*(buffer+6)][1];
			value7 = dither2x2[*(buffer)][*(buffer+2)][*(buffer+4)][*(buffer+6)][2];
			value8 = dither2x2[*(buffer)][*(buffer+2)][*(buffer+4)][*(buffer+6)][3];
			buffer += 8;

			*(offset) = 	value1 * 256 + value5;
			*(offset+40) = 	value2 * 256 + value6;
			*(offset+20) = 	value3 * 256 + value7;
			*(offset+60) = 	value4 * 256 + value8;
			offset += 1;
		}
		offset += 160 - COLUMNS/8;
    }
}
#pragma GCC pop_options