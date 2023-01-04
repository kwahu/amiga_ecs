#ifndef _C2P_H_
#define _C2P_H_

void ScreenToPlanes4x4(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void ScreenToPlanes2x2(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void GenDitherWord();
void GenDither4x4();
void GenDither4x4Shifted();
void GenDither2x2();

#endif