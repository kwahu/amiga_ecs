//#include "tracing.h"
#include <ace/utils/bitmap.h>
#include "../src_common/tracing.h"

unsigned short ditherWord[32][32][2];		//8kb
unsigned char ditherByte[32][32][4];		//4kb
unsigned short ditherByte256[32][32][4];	//8kb

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
void GenDitherByte256()
{
	for(int b = 0; b < 32; ++b)
	{
		for(int a = 0; a < 32; ++a)
		{			
			if(a % 2 || a == 0)
			{
				ditherByte256[a][b][0] = 0xf000 * (((a/2)>>0) & 1);
				ditherByte256[a][b][1] = 0xf000 * (((a/2)>>1) & 1);
				ditherByte256[a][b][2] = 0xf000 * (((a/2)>>2) & 1);
				ditherByte256[a][b][3] = 0xf000 * (((a/2)>>3) & 1);
			}
			else
			{
				ditherByte256[a][b][0] = 0xa000 * (((a/2)>>0) & 1);
				ditherByte256[a][b][1] = 0xa000 * (((a/2)>>1) & 1);
				ditherByte256[a][b][2] = 0xa000 * (((a/2)>>2) & 1);
				ditherByte256[a][b][3] = 0xa000 * (((a/2)>>3) & 1);
				ditherByte256[a][b][0] += 0x5000 * (((a/2-1)>>0) & 1); 
				ditherByte256[a][b][1] += 0x5000 * (((a/2-1)>>1) & 1);
				ditherByte256[a][b][2] += 0x5000 * (((a/2-1)>>2) & 1);
				ditherByte256[a][b][3] += 0x5000 * (((a/2-1)>>3) & 1);
			}
			if(b % 2 || b == 0)
			{
				ditherByte256[a][b][0] += 0x0f00 * (((b/2)>>0) & 1);
				ditherByte256[a][b][1] += 0x0f00 * (((b/2)>>1) & 1);
				ditherByte256[a][b][2] += 0x0f00 * (((b/2)>>2) & 1);
				ditherByte256[a][b][3] += 0x0f00 * (((b/2)>>3) & 1);
			}
			else
			{
				ditherByte256[a][b][0] += 0x0a00 * (((b/2)>>0) & 1);
				ditherByte256[a][b][1] += 0x0a00 * (((b/2)>>1) & 1);
				ditherByte256[a][b][2] += 0x0a00 * (((b/2)>>2) & 1);
				ditherByte256[a][b][3] += 0x0a00 * (((b/2)>>3) & 1);
				ditherByte256[a][b][0] += 0x0500 * (((b/2-1)>>0) & 1);
				ditherByte256[a][b][1] += 0x0500 * (((b/2-1)>>1) & 1);
				ditherByte256[a][b][2] += 0x0500 * (((b/2-1)>>2) & 1);
				ditherByte256[a][b][3] += 0x0500 * (((b/2-1)>>3) & 1);
			}
		}
	}
}
#pragma GCC push_options
#pragma GCC optimize ("peel-loops")

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
void ScreenToPlanesWordWord(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset;

	unsigned short value1, value2, value3, value4;

	for(unsigned char y = 0; y < ROWS; y++)
    {
		offset = (unsigned short *) planes + y * 320 + 80 * counter + yoffset * 80;

		for(unsigned char x = 0; x < COLUMNS*2; x+=8)
		{
			value1 = ditherWord[*(buffer+x+1+y*COLUMNS*2)][*(buffer+x+3+y*COLUMNS*2)][0];
			value2 = ditherWord[*(buffer+x+5+y*COLUMNS*2)][*(buffer+x+5+y*COLUMNS*2)][0];
			value3 = ditherWord[*(buffer+x+1+y*COLUMNS*2)][*(buffer+x+3+y*COLUMNS*2)][1];
			value4 = ditherWord[*(buffer+x+5+y*COLUMNS*2)][*(buffer+x+7+y*COLUMNS*2)][1];
			*(offset) = 	(value1 & 0xff00) + value2 / 256;
			*(offset+40) = 	(value1 & 0xff) * 256 + (value2 & 0xff);
			*(offset+20) = 	(value3 & 0xff00) + value4 / 256;
			*(offset+60) = 	(value3 & 0xff) * 256 + (value4 & 0xff);
			offset += 1; //go to next 2 pixels
		}
		
    }
}


void ScreenToPlanesTopDown(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes + 80 * counter + yoffset * 80;

	unsigned short value1, value2, value3, value4;

	buffer++;
	for(unsigned char y = 0; y < ROWS; y++)
    {

		for(unsigned short i = 0; i < (COLUMNS/4); i++)
		{
			value1 = ditherWord[*(buffer)][*(buffer+2)][0];
			value3 = ditherWord[*(buffer)][*(buffer+2)][1];
			buffer += 4;
			value2 = ditherWord[*(buffer)][*(buffer+2)][0];
			value4 = ditherWord[*(buffer)][*(buffer+2)][1];
			buffer += 4;

			*(offset) = 	(value1 & 0xff00) + value2 / 256;
			*(offset+40) = 	(value1 & 0xff) * 256 + (value2 & 0xff);
			*(offset+20) = 	(value3 & 0xff00) + value4 / 256;
			*(offset+60) = 	(value3 & 0xff) * 256 + (value4 & 0xff);
			offset += 1;
		}
		
		offset += 320 - COLUMNS/4;
    }
}


// UWORD bswap(ULONG x) {
//   UBYTE uwHi = x >> 8;
//   UBYTE uwLo = x & 0xFF;
//   return (uwLo << 8) | uwHi;
// }


void WriteWord(unsigned char *buffer, unsigned short *offset)
{
	unsigned short value1, value2, value3, value4;
	for(unsigned short i = 0; i < (COLUMNS/4); i++)
		{
			value1 = ditherWord[*(buffer)][*(buffer+2)][0];
			value3 = ditherWord[*(buffer)][*(buffer+2)][1];
			buffer += 4;
			value2 = ditherWord[*(buffer)][*(buffer+2)][0];
			value4 = ditherWord[*(buffer)][*(buffer+2)][1];
			buffer += 4;

			*(offset) = 	(value1 & 0xff00) + value2 / 256;
			*(offset+40) = 	(value1 & 0xff) * 256 + (value2 & 0xff);
			*(offset+20) = 	(value3 & 0xff00) + value4 / 256;
			*(offset+60) = 	(value3 & 0xff) * 256 + (value4 & 0xff);
			offset += 1;
		}
}

void WriteWordByte(unsigned char *buffer, unsigned short *offset)
{
	unsigned char value1, value2, value3, value4, value5, value6, value7, value8;
	for(unsigned short i = 0; i < (COLUMNS/4); i++)
		{
			value1 = ditherByte[*(buffer)][*(buffer+2)][0];
			value2 = ditherByte[*(buffer)][*(buffer+2)][1];
			value3 = ditherByte[*(buffer)][*(buffer+2)][2];
			value4 = ditherByte[*(buffer)][*(buffer+2)][3];
			buffer += 4;
			value5 = ditherByte[*(buffer)][*(buffer+2)][0];
			value6 = ditherByte[*(buffer)][*(buffer+2)][1];
			value7 = ditherByte[*(buffer)][*(buffer+2)][2];
			value8 = ditherByte[*(buffer)][*(buffer+2)][3];
			buffer += 4;

			*(offset) = 	value1 * 256 + value5;
			*(offset+40) = 	value2 * 256 + value6;
			*(offset+20) = 	value3 * 256 + value7;
			*(offset+60) = 	value4 * 256 + value8;
			offset += 1;
		}
}
void ScreenToPlanesUnrolledWord(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes + 80 * counter + yoffset * 80;



	buffer++;
	for(unsigned char y = 0; y < ROWS; y++)
    {

		WriteWord(buffer, offset);
		buffer += (COLUMNS/4)*8;
		offset += (COLUMNS/4);
		offset += 320 - COLUMNS/4;
    }
}

void ScreenToPlanesUnrolledByte(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes + 80 * counter + yoffset * 80;



	buffer++;
	for(unsigned char y = 0; y < ROWS; y++)
    {

		WriteWordByte(buffer, offset);
		buffer += (COLUMNS/4)*8;
		offset += (COLUMNS/4);
		offset += 320 - COLUMNS/4;
    }
}

void ScreenToPlanesUnrolledWholeByte(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes + 80 * counter + yoffset * 80;

	unsigned short value1, value2, value3, value4;
	unsigned char value5, value6, value7, value8;

	buffer++;
	for(unsigned char y = 0; y < ROWS; y++)
    {

		for(unsigned short i = 0; i < (COLUMNS/4); i++)
		{
			value1 = ditherByte256[*(buffer)][*(buffer+2)][0];
			value2 = ditherByte256[*(buffer)][*(buffer+2)][1];
			value3 = ditherByte256[*(buffer)][*(buffer+2)][2];
			value4 = ditherByte256[*(buffer)][*(buffer+2)][3];
			buffer += 4;
			value5 = ditherByte[*(buffer)][*(buffer+2)][0];
			value6 = ditherByte[*(buffer)][*(buffer+2)][1];
			value7 = ditherByte[*(buffer)][*(buffer+2)][2];
			value8 = ditherByte[*(buffer)][*(buffer+2)][3];
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
void ScreenToPlanesUnrolledWholeWord(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
{
	unsigned short *offset = (unsigned short *) planes + 80 * counter + yoffset * 80;

	unsigned short value1, value2, value3, value4;

	buffer++;
	for(unsigned char y = 0; y < ROWS; y++)
    {

			for(unsigned short i = 0; i < (COLUMNS/4); i++)
		{
			value1 = ditherWord[*(buffer)][*(buffer+2)][0];
			value3 = ditherWord[*(buffer)][*(buffer+2)][1];
			buffer += 4;
			value2 = ditherWord[*(buffer)][*(buffer+2)][0];
			value4 = ditherWord[*(buffer)][*(buffer+2)][1];
			buffer += 4;

			*(offset) = 	(value1 & 0xff00) + value2 / 256;
			*(offset+40) = 	(value1 & 0xff) * 256 + (value2 & 0xff);
			*(offset+20) = 	(value3 & 0xff00) + value4 / 256;
			*(offset+60) = 	(value3 & 0xff) * 256 + (value4 & 0xff);
			offset += 1;
		
		}

		//buffer += (COLUMNS/4)*8;
		//offset += (COLUMNS/4);
		offset += 320 - COLUMNS/4;
    }
}
#pragma GCC pop_options

// void ScreenToPlanesByte(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset)
// {
// 	unsigned char *offset;
// 	unsigned char *bufPos;

// 	//unsigned short value1, value2, value3, value4;

// 	for(unsigned char y = ROWS; y > 0; y--)
//     {
// 		offset =  planes + (ROWS - y) * 640 + 160 * counter + yoffset * 160;
// 		bufPos = buffer + y*COLUMNS;

// 		for(unsigned char x = 0; x < COLUMNS; x+=2)
// 		{
// 			*(offset) = ditherByte[*(bufPos)][*(bufPos+1)][0];
// 			*(offset+40) = ditherByte[*(bufPos)][*(bufPos+1)][1];
// 			*(offset+80) = ditherByte[*(bufPos)][*(bufPos+1)][2];
// 			*(offset+120) = ditherByte[*(bufPos)][*(bufPos+1)][3];
// 			offset += 1; //go to next 2 pixels
// 			bufPos += 2;
// 		}
//     }
// }

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