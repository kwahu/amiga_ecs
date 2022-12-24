#include "tracing.h"
#include "std.h"

unsigned char *map;
unsigned short anglesWord[COLUMNS][DEPTH];
unsigned char anglesByte[COLUMNS][DEPTH];
char heightsByte[ROWS][DEPTH];
//short heightsWord[ROWS][DEPTH];
unsigned char *screenByte;
unsigned short *screenWord;
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
    for(unsigned short y = 0; y < MAPLENGTH; y++)
    {
        for(unsigned short x = 0; x < MAPWIDTH; x++)
        {
            *(map+x*2+y*MAPWIDTH*2) = sin256(x*2)/2 + sin256(y*2)/4;
            *(map+x*2+1+y*MAPWIDTH*2) = y % 32;//sin256(x)/16 + sin256(y*8)/16;//sin256(x*8+y*16)/9+2;
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
            *(map+xx*2+yy*MAPWIDTH*2) = sin16(xx*4+yy*4+counter*2);
        }
    }
}


/**
			 * Angles() - Calculates the angles of the columns and depths
			 * 
			 * Iterates through each column and depth and assigns the value of 256 to each angle
			 */
void AnglesByte(void)
{
    short angle = 0;
    //char column = 0;
    for(unsigned char col = 0; col < COLUMNS; col++)
    {
        for(unsigned char depth = 0; depth < DEPTH; depth++)
        {
            angle = ((col-COLUMNS/2)*(depth)) /64;
            //column = (col-COLUMNS/2)/4;
            //next line & +/- angle & starting width of the screen
            //+ (column - column % 2)
            anglesByte[col][depth] = MAPWIDTH*2  + (angle - angle % 2); //make sure its even
        }
    }
}
void AnglesWord(void)
{
    short angle = 0;
    //char column = 0;
    for(unsigned char col = 0; col < COLUMNS; col++)
    {
        for(unsigned char depth = 0; depth < DEPTH; depth++)
        {
            angle = ((col-COLUMNS/2)*depth) /128;
            //column = (col-COLUMNS/2)/4;
            //next line & +/- angle & starting width of the screen
            //+ (column - column % 2)
            anglesWord[col][depth] = MAPWIDTH*2  + (angle - angle % 2) ; //make sure its even
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
void HeightByte(void)
{
    for(unsigned char row = 0; row < ROWS; row++)
    {
        for(unsigned char depth = 0; depth < DEPTH; depth++)
        {
            heightsByte[row][depth] = ((row - ROWS/2)* (depth+0))/4 ;
        }
    }
}
// void HeightWord(void)
// {
//     for(unsigned char row = 0; row < ROWS; row++)
//     {
//         for(unsigned char depth = 0; depth < DEPTH; depth++)
//         {
//             heightsWord[row][depth] = (((row - ROWS/2)* depth)/4 ) * 256;
//         }
//     }
// }



/**
 * PathTracing() is a function that traces a path from a given player's x, y, and z coordinates
 * to a given map. It will then update the color and depth of the screen and depth buffer accordingly.
 * 
 * @param playerX The x coordinate of the player.
 * @param playerY The y coordinate of the player.
 * @param playerZ The z coordinate of the player.
 */
void PathTracingByte(unsigned char playerX, unsigned char playerY, unsigned char playerZ) {
    unsigned char *mapPointer;
    unsigned char mapHeight;
    unsigned char color;
    unsigned char row;
    unsigned char depth;    
    unsigned char *start = map + playerX*2 + playerY*MAPWIDTH*2;
    unsigned short offset;

    for(unsigned char col = 0; col < COLUMNS; col++) {  //for each x point in a row on a screen
        mapPointer = start + (col-COLUMNS/2) - (col-COLUMNS/2) % 2;
        offset = col;
        row = 0; depth = 1;                   //reset the row, depth, and color
        while(row < ROWS) {                             //until all rows are done
            mapHeight = *(mapPointer);                  //read map height at current pathtrace point
            if( mapHeight > heightsByte[row][depth] + playerZ ) {     //check if pathtrace hit the right height
                color = *(mapPointer+1);                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!update the color
                *(screenByte+offset) = color;               //write the color to the screen
                *(zbuffer+offset) = depth;              //write the depth to the depth buffer
                row++;                                  //move to the next row
                offset += COLUMNS;                      //move to the next row
            } else {                                    //if we dont find the right height
                if(depth < DEPTH - 1) {                     //check if we are not at the end of the depth
                    mapPointer += anglesWord[col][depth];   //move pathtrace to the next depth
                    depth++;                            //move to the next depth
                } else {                                //fill the rest of the screen with background
                    while(row < ROWS) {
                        *(screenByte+offset) = 0;           //write the color to the screen
                        *(zbuffer+offset) = 0;          //write the depth to the depth buffer
                        row++;                        //move to the next depth
                        offset += COLUMNS;                      //move to the next row
                    }
                }
            }
        }
    }    
}
void PathTracingWord(unsigned char playerX, unsigned char playerY, unsigned char playerZ) {
    unsigned char *mapPointer;
    unsigned char row;
    unsigned char depthByte;   
    unsigned short depthWord;   
    unsigned short offset;
    unsigned char finalDepth = DEPTH - 1;

    for(unsigned char col = 0; col < COLUMNS; col++) {  //for each x point in a row on a screen
        row = 0; depthByte = 0; depthWord = 0x0200;
        mapPointer = map + playerX*2 + playerY*MAPWIDTH*2 + (col-COLUMNS/2)  - ((col-COLUMNS/2)) % 2;
        offset = col;
                  
        
        while(row < ROWS) {                             //until all rows are done
            if(*(mapPointer) > (unsigned char)(heightsByte[row][depthByte] + playerZ) ) {     //check if pathtrace hit the right height
                *(screenWord+offset) =*(mapPointer+1) + depthWord;               //write the color to the screen
                row++;                                  //move to the next row
                offset += COLUMNS;                      //move to the next row
            } else {                                    //if we dont find the right height
                if(depthByte < finalDepth) {                     //check if we are not at the end of the depth
                    mapPointer += anglesByte[col][depthByte];   //move pathtrace to the next depth
                    depthByte++;                            //move to the next depth
                    depthWord += 0x0100;
                } else {                                //fill the rest of the screen with background
                    while(row < ROWS) {
                        *(screenWord+offset) = 0 + 0;           //write the color to the screen
                        row++;                        //move to the next depth
                        offset += COLUMNS;                      //move to the next row
                    }
                }
            }
        }
    }    
}