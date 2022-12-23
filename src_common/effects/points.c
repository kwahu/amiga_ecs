//list of 3d points
// 3d points are used for 3d effects
#define POINTS 100
unsigned char points[POINTS][3];

//array of precalculated divisions
//used for 3d effects
unsigned char divs[64][64];

// void GenDivs()
// {
//     for(int i = 0; i < 64; ++i)
//     {
//         for(int j = 0; j < 64; ++j)
//         {
//             divs[i][j] = i * 64 / j;
//         }
//     }
// }

// void GenSphere()
// {
//     //generate 64 points
//     for(unsigned char i = 0; i < 64; ++i)
//     {
//         //generate 3d point
//         points[i][0] = cos(i * 2 * PI / 64) * 64;
//         points[i][1] = sin(i * 2 * PI / 64) * 64;
//         points[i][2] = sin(i * 2 * PI / 64) * 64;
//     }
// }


// void DrawPoints()
// {
//     //convert 3d points to 2d points on screen
//     for(unsigned char i = 0; i < POINTS; ++i)
//     {
//         //convert 3d point to 2d point
//         unsigned char x = divs[ points[i][0] * 64 ][ points[i][2] + 64 ];
//         unsigned char y = divs[ points[i][1] * 64 ][ points[i][2] + 64 ];
//         //draw 2d point on screen
//         if(x >= 0 && x < 64 && y >= 0 && y < 64)
//             screen[x + y * 64] = 255;
//     }
// }

