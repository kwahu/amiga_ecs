#ifndef _C2P_H_
#define _C2P_H_

void ScreenToPlanesWord(unsigned char *screen, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void ScreenToPlanesByte(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void GenDitherWord();
void GenDitherByte();

#endif