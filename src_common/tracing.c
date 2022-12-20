#include "tracing.h"
#include "std.h"

unsigned char *map;
//unsigned char angle[COLUMNS];
unsigned short angles[COLUMNS][DEPTH];
char heights[ROWS][DEPTH];
unsigned char *screen;
unsigned char *zbuffer;


/**
			 * Generates a map with a given size.
			 * 
			 * @param x The x-coordinate of the map.
			 * @param y The y-coordinate of the map.
			 */
void GenMap()
{
    for(unsigned char y = 0; y < 255; y++)
    {
        for(unsigned char x = 0; x < 255; x++)
        {
            *(map+x+y*256) = sin16(x*8)*2;
            if(x > 10 && x < 20)
                *(map+x+y*256) = 2;
        }
    }
}

/**
			 * TransformMap() - Transforms a section of a map with a given counter
			 * 
			 * @param counter - The counter used to transform the map
			 * @param x - The x coordinate of the starting point of the map section
			 * @param y - The y coordinate of the starting point of the map section
			 * @param sizeX - The width of the map section
			 * @param sizeY - The height of the map section
			 */

void TransformMap(unsigned char counter, unsigned char x, unsigned char y, unsigned char sizeX, unsigned char sizeY)
{
    for(unsigned char xx = x; xx < x+sizeX; xx++)
    {
        for(unsigned char yy = y; yy < y+sizeY; yy++)
        {
            *(map+xx+yy*256) = sin16(xx*2+yy*2+counter);
        }
    }
}


/**
			 * Angles() - Calculates the angles of the columns and depths
			 * 
			 * Iterates through each column and depth and assigns the value of 256 to each angle
			 */
void Angles(void)
{
    for(unsigned char col = 0; col < COLUMNS; col++)
    {
        for(unsigned char depth = 0; depth < DEPTH; depth++)
        {
            //next line & +/- angle & starting width of the screen
            angles[col][depth] = 256 + ((col-COLUMNS/2)*depth)/32;// + (col-COLUMNS/2)/8;
        }
    }
}



/**
 			* Height() - Calculates the height of each row and depth
 			* @param void
 			* @return void
 			*/
void Height(void)
{
    for(unsigned char row = 0; row < ROWS; row++)
    {
        for(unsigned char depth = 0; depth < DEPTH; depth++)
        {
            heights[row][depth] = ((row - ROWS/2)* depth)/4 ;
        }
    }
}



/**
 * PathTracing() is a function that traces a path from a given player's x, y, and z coordinates
 * to a given map. It will then update the color and depth of the screen and depth buffer accordingly.
 * 
 * @param playerX The x coordinate of the player.
 * @param playerY The y coordinate of the player.
 * @param playerZ The z coordinate of the player.
 */
void PathTracing(unsigned char playerX, unsigned char playerY, unsigned char playerZ) {
    unsigned char *mapPointer;
    unsigned char mapHeight;
    unsigned char color;
    unsigned char row;
    unsigned char depth;    
    unsigned char *start = map + playerX + playerY*256;
    unsigned short offset;

    for(unsigned char col = 0; col < COLUMNS; col++) {  //for each x point in a row on a screen
        mapPointer = start;
        offset = col;
        row = 0; depth = 0;                   //reset the row, depth, and color
        while(row < ROWS) {                             //until all rows are done
            mapHeight = *(mapPointer);                  //read map height at current pathtrace point
            if( mapHeight > heights[row][depth] + playerZ ) {     //check if pathtrace hit the right height
                color = *(mapPointer);                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!update the color
                *(screen+offset) = color;               //write the color to the screen
                *(zbuffer+offset) = depth;              //write the depth to the depth buffer
                row++;                                  //move to the next row
                offset += COLUMNS;                      //move to the next row
            } else {                                    //if we dont find the right height
                if(depth < DEPTH - 1) {                     //check if we are not at the end of the depth
                    mapPointer += angles[col][depth];   //move pathtrace to the next depth
                    depth++;                            //move to the next depth
                } else {                                //fill the rest of the screen with background
                    while(row < ROWS) {
                        *(screen+offset) = 0;           //write the color to the screen
                        *(zbuffer+offset) = 0;          //write the depth to the depth buffer
                        row++;                        //move to the next depth
                        offset += COLUMNS;                      //move to the next row
                    }
                }
            }
        }
    }    
}