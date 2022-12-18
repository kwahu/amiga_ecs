#include "tracing.h"
#include "std.h"

unsigned char map[256][256];
//unsigned char angle[COLUMNS];
unsigned char angles[COLUMNS][DEPTH];
unsigned char heights[ROWS][DEPTH];
unsigned char *screen;
unsigned char zbuffer[COLUMNS][ROWS];

//generate a map
void GenMap()
{
    for(unsigned char y = 0; y < 255; y++)
    {
        for(unsigned char x = 0; x < 255; x++)
        {
            map[x][y] = sin16(x*2+y);
        }
    }
}

void TransformMap(unsigned char counter, unsigned char x, unsigned char y, unsigned char sizeX, unsigned char sizeY)
{
    for(unsigned char i = x; i < x+sizeX; i++)
    {
        for(unsigned char j = y; j < y+sizeY; j++)
        {
            map[i][j] = sin16(i*2+j*2+counter);
        }
    }
}



//probably 45 degrees in each direction
void Angles2(void)
{
    for(unsigned char i = 0; i < COLUMNS; i++)
    {
        for(unsigned char j = 0; j < DEPTH; j++)
        {
            angles[i][j] = COLUMNS/2*4 + i*4;
        }
    }
}

//generate a height table
void Height(void)
{
    for(unsigned char i = 0; i < ROWS; i++)
    {
        for(unsigned char j = 0; j < DEPTH; j++)
        {
            heights[i][j] = i/2 + j/16;
        }
    }
}

void PathTracing(unsigned char playerX, unsigned char playerY) {
    //unsigned short int mapPosition = 0;
    //short int mapStep;
    unsigned char *mapPointer;
    unsigned char mapHeight;
    unsigned char color;
    unsigned char row;
    unsigned char depth;

    for(unsigned char col = 0; col < COLUMNS; col++) {  //for each x point in a row on a screen
        mapPointer = &map[playerX][playerY];                      //start at the x screen position of the map
        row = 0; depth = 0; color = 0;                  //reset the row, depth, and color
        while(row < ROWS) {                             //until all rows are done
            mapHeight = *(mapPointer);                  //read map height at current pathtrace point
            if( mapHeight > heights[row][depth] ) {     //check if pathtrace hit the right height
                color = *(mapPointer+1);                //update the color
                *(screen+col+row*COLUMNS) = color;               //write the color to the screen
                zbuffer[col][row] = depth;              //write the depth to the depth buffer
                row++;                                  //move to the next row
            } else {                                    //if we dont find the right height
                if(depth < DEPTH) {                     //check if we are not at the end of the depth
                    mapPointer += angles[col][depth];   //move pathtrace to the next depth
                    depth++;                            //move to the next depth
                } else {                                //fill the rest of the screen with background
                    while(row < ROWS) {
                        *(screen+col+row*COLUMNS) = 0;           //write the color to the screen
                        zbuffer[col][row] = 0;          //write the depth to the depth buffer
                        row++;                        //move to the next depth
                    }
                }
            }
        }
    }    
}

void Test2(void)
{

}