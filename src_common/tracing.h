#ifndef _TRACING_H_
#define _TRACING_H_
  
//step along the depth of the map for each point on the screen - 
#define COLUMNS 32
#define ROWS 64
#define DEPTH 16

extern unsigned char map[128][128];
extern unsigned char angle[COLUMNS];
extern unsigned char angles[COLUMNS][DEPTH];
extern unsigned char heights[ROWS][DEPTH];
extern unsigned char *screen;
extern unsigned char zbuffer[COLUMNS][ROWS];

void GenMap(void);
void Angles(void);
void Angles2(void);
void Height(void);
void Test1(unsigned char counter);
void Test2(void);

#endif