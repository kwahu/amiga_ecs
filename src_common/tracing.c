#include "tracing.h"
#include "std.h"

unsigned char *map;
unsigned short angles[COLUMNS][DEPTH];
char heights[ROWS][DEPTH];
unsigned char *screen;
unsigned char *zbuffer;

unsigned short screenPositionX[COLUMNS][DEPTH];
unsigned short screenPositionY[ROWS][DEPTH];

//
/**
			 * Generates a map with a given size.
			 * 
			 * @param x The x-coordinate of the map.
			 * @param y The y-coordinate of the map.
			 */
void GenMap()
{
    for(unsigned char y = 0; y < MAPSIZE; y++)
    {
        for(unsigned char x = 0; x < MAPSIZE; x++)
        {
            *(map+x*2+y*MAPSIZE*2) = sin256(x*2)/5 + sin256(y*2)/10;
            *(map+x*2+1+y*MAPSIZE*2) = sin256(x*2)/16 + sin256(y*8)/16;//sin256(x*8+y*16)/9+2;
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
            *(map+xx*2+yy*MAPSIZE*2) = sin16(xx*4+yy*4+counter*2);
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
    char angle = 0;
    //char column = 0;
    for(unsigned char col = 0; col < COLUMNS; col++)
    {
        for(unsigned char depth = 0; depth < DEPTH; depth++)
        {
            angle = ((col-COLUMNS/2)*depth)/32;
            //column = (col-COLUMNS/2)/4;
            //next line & +/- angle & starting width of the screen
            //+ (column - column % 2)
            angles[col][depth] = MAPSIZE*2  + (angle - angle % 2); //make sure its even
        }
    }
}

// -32 to 32
// 0 to 64
// vodi SpaceToScreen()
// {
//     for(unsigned char col = 0; col < COLUMNS; col++)
//     {
//         for(unsigned char depth = 0; depth < DEPTH; depth++)
//         {
//             screenPositionX[col][depth] = ( ( col - COLUMNS/2) - depth )  ;
//         }
//     }
//     for(unsigned char row = 0; row < ROWS; row++)
//     {
//         for(unsigned char depth = 0; depth < DEPTH; depth++)
//         {
//             screenPositionY[row][depth] = ((row - ROWS/2)* depth)/4 ;
//         }
//     }
// }



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
    unsigned char *start = map + playerX*2 + playerY*MAPSIZE*2;
    unsigned short offset;

    for(unsigned char col = 0; col < COLUMNS; col++) {  //for each x point in a row on a screen
        mapPointer = start + (col-COLUMNS/2) - (col-COLUMNS/2) % 2;
        offset = col;
        row = 0; depth = 2;                   //reset the row, depth, and color
        while(row < ROWS) {                             //until all rows are done
            mapHeight = *(mapPointer);                  //read map height at current pathtrace point
            if( mapHeight > heights[row][depth] + playerZ ) {     //check if pathtrace hit the right height
                color = *(mapPointer+1);                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!update the color
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