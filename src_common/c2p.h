#ifndef _C2P_H_
#define _C2P_H_

void ScreenToPlanes32(unsigned char *screen, unsigned char *planes[4], unsigned char counter);
void ScreenToPlanes64(unsigned char *buffer, unsigned char *planes[4], unsigned char counter, unsigned char yoffset);
void ScreenToPlanes64tunel(unsigned char *buffer, unsigned char *planes[4], unsigned char counter, unsigned char yoffset);
void GenDither32();
void GenDither64();



#endif