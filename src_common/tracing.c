#include "tracing.h"
#include "std.h"

unsigned char map[256][256];
//unsigned char angle[COLUMNS];
unsigned short angles[COLUMNS][DEPTH];
char heights[ROWS][DEPTH];
unsigned char *screen;
unsigned char *zbuffer;

//generate a map
void GenMap()
{
    for(unsigned char y = 0; y < 255; y++)
    {
        for(unsigned char x = 0; x < 255; x++)
        {
            map[x][y] = sin16(x*2)/4+sin16(y)/4;
            if(x == 100 || x == 200)
                map[x][y] += 8;
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


//generate table of ray traveling on an angle trhough a map table
//map is 256x256, the ray is DEPTH long, and the angle is 45 degrees
//each rain in a column, of the size of COLUMN, is traveling at an angle that in the middle of the column is 0 degrees and at the edges is 45 degrees
//the angle is calculated by the distance from the middle of the column
//the angle is then used to calculate the step in the map table
//the step is the number of columns in the map table that the ray travels in one step
//the step is calculated by the angle and the depth of the ray
//the step is then used to calculate the next point in the map table that the ray travels to
//the ray is then drawn to the screen
void Angles(void)
{
    for(unsigned char col = 0; col < COLUMNS; col++)
    {
        for(unsigned char depth = 0; depth < DEPTH; depth++)
        {
            angles[col][depth] = 256 + ((col-COLUMNS/2)*depth)/32 + (col-COLUMNS/2)/8;
        }
    }
}


//generate a height table
void Height(void)
{
    for(unsigned char row = 0; row < ROWS; row++)
    {
        for(unsigned char depth = 0; depth < DEPTH; depth++)
        {
            heights[row][depth] = ((row - ROWS/2)* depth)/8 ;
        }
    }
}


//TODO - remove DEPTH protection from the while loop
void PathTracing(unsigned char playerX, unsigned char playerY, unsigned char playerZ) {
    //unsigned short int mapPosition = 0;
    //short int mapStep;
    unsigned char *mapPointer;
    unsigned char mapHeight;
    unsigned char color;
    unsigned char row;
    unsigned char depth;

    for(unsigned char col = 0; col < COLUMNS; col++) {  //for each x point in a row on a screen
        mapPointer = &map[playerX][playerY];         //-COLUMNS/2+col             //start at the x screen position of the map
        row = 0; depth = 0; color = 0;                  //reset the row, depth, and color
        while(row < ROWS) {                             //until all rows are done
            mapHeight = *(mapPointer);                  //read map height at current pathtrace point
            if( mapHeight > heights[row][depth] + playerZ ) {     //check if pathtrace hit the right height
                color = *(mapPointer);                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!update the color
                *(screen+col+row*COLUMNS) = color;               //write the color to the screen
                *(zbuffer+col+row*COLUMNS) = DEPTH/2 - 1 - depth/2;              //write the depth to the depth buffer
                row++;                                  //move to the next row
            } else {                                    //if we dont find the right height
                if(depth < DEPTH - 1) {                     //check if we are not at the end of the depth
                    mapPointer += angles[col][depth];   //move pathtrace to the next depth
                    depth++;                            //move to the next depth
                } else {                                //fill the rest of the screen with background
                    while(row < ROWS) {
                        *(screen+col+row*COLUMNS) = 0;           //write the color to the screen
                        *(zbuffer+col+row*COLUMNS) = 0;          //write the depth to the depth buffer
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