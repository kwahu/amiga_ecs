#ifndef _TRACING_H_
#define _TRACING_H_
  
//step along the depth of the map for each point on the screen - 
#define COLUMNS 64
#define ROWS 32
#define DEPTH 16
#define MAPSIZE 128

extern unsigned char *map;
extern unsigned short angles[COLUMNS][DEPTH];
extern char heights[ROWS][DEPTH];
extern unsigned char *screen;
extern unsigned char *zbuffer;

void GenMap();
void TransformMap(unsigned char counter, unsigned char x, unsigned char y, unsigned char sizeX, unsigned char sizeY);
void Angles(void);
void Height(void);
void PathTracing(unsigned char playerX, unsigned char playerY, unsigned char playerZ);
void PathTracingArray(unsigned char playerX, unsigned char playerY, unsigned char playerZ);
void Test2(void);

#endif