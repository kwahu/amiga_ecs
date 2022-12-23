//#include "tracing.h"
#include <ace/utils/bitmap.h>
#include "../src_common/tracing.h"

unsigned short ditherWord[32][32][2];
unsigned char ditherByte[32][32][4];

void GenDitherWord()
{
	for(int b = 0; b < 32; ++b)
	{
		for(int a = 0; a < 32; ++a)
		{			
			if(a % 2 || a == 0)
			{
				ditherWord[a][b][0] = 0xf000 * (((a/2)>>0) & 1)  + 0xf0 * (((a/2)>>2) & 1);
				ditherWord[a][b][1] = 0xf000 * (((a/2)>>1) & 1)  + 0xf0 * (((a/2)>>3) & 1);
			}
			else
			{
				ditherWord[a][b][0] = 0xa000 * (((a/2)>>0) & 1) + 0xa0 * (((a/2)>>2) & 1);
				ditherWord[a][b][1] = 0xa000 * (((a/2)>>1) & 1) + 0xa0 * (((a/2)>>3) & 1);
				ditherWord[a][b][0] += 0x5000 * (((a/2-1)>>0) & 1) + 0x50 * (((a/2-1)>>2) & 1);
				ditherWord[a][b][1] += 0x5000 * (((a/2-1)>>1) & 1) + 0x50 * (((a/2-1)>>3) & 1);
			}
			if(b % 2 || b == 0)
			{
				ditherWord[a][b][0] += 0x0f00 * (((b/2)>>0) & 1) + 0x0f * (((b/2)>>2) & 1);
				ditherWord[a][b][1] += 0x0f00 * (((b/2)>>1) & 1)  + 0x0f * (((b/2)>>3) & 1);
			}
			else
			{
				ditherWord[a][b][0] += 0x0a00 * (((b/2)>>0) & 1) + 0x0a * (((b/2)>>2) & 1);
				ditherWord[a][b][1] += 0x0a00 * (((b/2)>>1) & 1) + 0x0a * (((b/2)>>3) & 1);
				ditherWord[a][b][0] += 0x0500 * (((b/2-1)>>0) & 1) + 0x05 * (((b/2-1)>>2) & 1);
				ditherWord[a][b][1] += 0x0500 * (((b/2-1)>>1) & 1) + 0x05 * (((b/2-1)>>3) & 1);
			}
		}
	}
}
void GenDitherByte()
{
	for(int b = 0; b < 32; ++b)
	{
		for(int a = 0; a < 32; ++a)
		{			
			if(a % 2 || a == 0)
			{
				ditherByte[a][b][0] = 0xf0 * (((a/2)>>0) & 1);
				ditherByte[a][b][1] = 0xf0 * (((a/2)>>1) & 1);
				ditherByte[a][b][2] = 0xf0 * (((a/2)>>2) & 1);
				ditherByte[a][b][3] = 0xf0 * (((a/2)>>3) & 1);
			}
			else
			{
				ditherByte[a][b][0] = 0xa0 * (((a/2)>>0) & 1);
				ditherByte[a][b][1] = 0xa0 * (((a/2)>>1) & 1);
				ditherByte[a][b][2] = 0xa0 * (((a/2)>>2) & 1);
				ditherByte[a][b][3] = 0xa0 * (((a/2)>>3) & 1);
				ditherByte[a][b][0] += 0x50 * (((a/2-1)>>0) & 1); 
				ditherByte[a][b][1] += 0x50 * (((a/2-1)>>1) & 1);
				ditherByte[a][b][2] += 0x50 * (((a/2-1)>>2) & 1);
				ditherByte[a][b][3] += 0x50 * (((a/2-1)>>3) & 1);
			}
			if(b % 2 || b == 0)
			{
				ditherByte[a][b][0] += 0x0f * (((b/2)>>0) & 1);
				ditherByte[a][b][1] += 0x0f * (((b/2)>>1) & 1);
				ditherByte[a][b][2] += 0x0f * (((b/2)>>2) & 1);
				ditherByte[a][b][3] += 0x0f * (((b/2)>>3) & 1);
			}
			else
			{
				ditherByte[a][b][0] += 0x0a * (((b/2)>>0) & 1);
				ditherByte[a][b][1] += 0x0a * (((b/2)>>1) & 1);
				ditherByte[a][b][2] += 0x0a * (((b/2)>>2) & 1);
				ditherByte[a][b][3] += 0x0a * (((b/2)>>3) & 1);
				ditherByte[a][b][0] += 0x05 * (((b/2-1)>>0) & 1);
				ditherByte[a][b][1] += 0x05 * (((b/2-1)>>1) & 1);
				ditherByte[a][b][2] += 0x05 * (((b/2-1)>>2) & 1);
				ditherByte[a][b][3] += 0x05 * (((b/2-1)>>3) & 1);
			}
		}
	}
}

void ScreenToPlanesWord(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset;

	unsigned short value1, value2, value3, value4;

	for(unsigned char y = ROWS; y > 0; y--)
    {
		offset = (unsigned short *) planes + (ROWS - y) * 320 + 80 * counter + yoffset * 80;

		for(unsigned char x = 0; x < COLUMNS; x+=4)
		{
			value1 = ditherWord[*(buffer+x+y*COLUMNS)][*(buffer+x+1+y*COLUMNS)][0];
			value2 = ditherWord[*(buffer+x+2+y*COLUMNS)][*(buffer+x+3+y*COLUMNS)][0];
			value3 = ditherWord[*(buffer+x+y*COLUMNS)][*(buffer+x+1+y*COLUMNS)][1];
			value4 = ditherWord[*(buffer+x+2+y*COLUMNS)][*(buffer+x+3+y*COLUMNS)][1];
			*(offset) = 	(value1 & 0xff00) + value2 / 256;
			*(offset+40) = 	(value1 & 0xff) * 256 + (value2 & 0xff);
			*(offset+20) = 	(value3 & 0xff00) + value4 / 256;
			*(offset+60) = 	(value3 & 0xff) * 256 + (value4 & 0xff);
			offset += 1; //go to next 2 pixels
		}
		
    }
}

void ScreenToPlanesByte(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned char *offset;
	unsigned char *bufPos;

	//unsigned short value1, value2, value3, value4;

	for(unsigned char y = ROWS; y > 0; y--)
    {
		offset =  planes + (ROWS - y) * 640 + 160 * counter + yoffset * 160;
		bufPos = buffer + y*COLUMNS;

		for(unsigned char x = 0; x < COLUMNS; x+=2)
		{
			*(offset) = ditherByte[*(bufPos)][*(bufPos+1)][0];
			*(offset+40) = ditherByte[*(bufPos)][*(bufPos+1)][1];
			*(offset+80) = ditherByte[*(bufPos)][*(bufPos+1)][2];
			*(offset+120) = ditherByte[*(bufPos)][*(bufPos+1)][3];
			offset += 1; //go to next 2 pixels
			bufPos += 2;
		}
    }
}

// void ScreenToPlanes64(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
// {
// 	unsigned short *offset;

// 	unsigned short value1, value2;//, value3, value4;

// 	for(unsigned char y = ROWS; y > 0; y--)
//     {
// 		offset = (unsigned short *) planes + (ROWS - y) * 320 + 80 * counter + yoffset * 80;

// 		for(unsigned char x = 0; x < COLUMNS; x+=4)
// 		{
// 			value1 = dither[*(buffer+x+y*COLUMNS)][*(buffer+x+1+y*COLUMNS)][1];
// 			value2 = dither[*(buffer+x+2+y*COLUMNS)][*(buffer+x+3+y*COLUMNS)][1];
// 			*(offset+20) = 	(value1 & 0xff00) + value2 / 256;
// 			*(offset+60) = 	(value1 & 0xff) * 256 + (value2 & 0xff);
// 			offset += 1; //go to next 2 pixels
// 		}
// 		offset = (unsigned short *) planes + (ROWS - y) * 320 + 80 * counter + yoffset * 80;
// 		for(unsigned char x = 0; x < COLUMNS; x+=4)
// 		{
// 			value1 = dither[*(buffer+x+y*COLUMNS)][*(buffer+x+1+y*COLUMNS)][0];
// 			value2 = dither[*(buffer+x+2+y*COLUMNS)][*(buffer+x+3+y*COLUMNS)][0];
// 			*(offset) = 	(value1 & 0xff00) + value2 / 256;
// 			*(offset+40) = 	(value1 & 0xff) * 256 + (value2 & 0xff);
// 			offset += 1; //go to next 2 pixels
// 		}
//     }
// }