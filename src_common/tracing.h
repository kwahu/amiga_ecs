#ifndef _TRACING_H_
#define _TRACING_H_
  
//step along the depth of the map for each point on the screen - 
#define COLUMNS 64
#define ROWS 60
#define DEPTH 32
#define MAPWIDTH 64
#define MAPLENGTH 128

extern unsigned char *map;
//extern unsigned char angles[COLUMNS][DEPTH];
extern char heightsByte[ROWS][DEPTH];
//extern short heightsWord[ROWS][DEPTH];
extern unsigned char *screenByte;
extern unsigned short *screenWord;
extern unsigned char *zbuffer;
extern unsigned char *pAnglesByte;
extern unsigned char *pHeightsByte;

void GenMap();
void TransformMap(unsigned char counter, unsigned char x, unsigned char y, unsigned char sizeX, unsigned char sizeY);
void AnglesByte(void);
void AnglesWord(void);
void HeightByte(void);
void HeightWord(void);
void CalculateRayCasts(void);
void PathTracingByte(unsigned char playerX, unsigned char playerY, unsigned char playerZ);
void PathTracingWord(unsigned char playerX, unsigned char playerY, unsigned char playerZ);
void PathTracingWordPointer(unsigned char playerX, unsigned char playerY, unsigned char playerZ);
void Test2(void);

#endif