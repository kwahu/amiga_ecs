#ifndef _C2P_H_
#define _C2P_H_


void ScreenToPlanesUnrolledByte(unsigned char *screen, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void ScreenToPlanesUnrolledWord(unsigned char *screen, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void ScreenToPlanesUnrolledWholeByte(unsigned char *screen, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void ScreenToPlanesUnrolledWholeWord(unsigned char *screen, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void ScreenToPlanesTopDown(unsigned char *screen, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void ScreenToPlanesWordWord(unsigned char *screen, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void ScreenToPlanesWord(unsigned char *screen, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void ScreenToPlanesByte(unsigned char *buffer, unsigned char *planes, unsigned char counter, unsigned char yoffset);
void GenDitherWord();
void GenDitherByte();
void GenDitherByte256();

#endif