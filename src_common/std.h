#ifndef _STD_H_
#define _STD_H_

extern unsigned char sinus256[256];
extern unsigned char sinus16[256];

void ConvertIntToChar(int number, char *test, int size);
unsigned char sin256(unsigned char value);
unsigned char sin16(unsigned char value);
void genSinusTable();


#endif