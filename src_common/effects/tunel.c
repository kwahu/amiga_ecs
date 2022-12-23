// unsigned char texWidth, texHeight;
// unsigned char texture[texWidth][texHeight];
// #define SCREENW 64
// #define SCREENH 32

// unsigned char distanceTable[SCREENW][SCREENH];
// //angleTable
// unsigned char angleTable[SCREENW][SCREENH];


// void generateTexture()
// {
// for(int y = 0; y < texHeight; y++)
//   for(int x = 0; x < texWidth; x++)
//   {
//     texture[y][x] = (x * 256 / texWidth) ^ (y * 256 / texHeight);
//   }
// }

// //generate non-linear transformation table
// void generateTables()
// {
//   for(int y = 0; y < SCREENH; y++)
//   for(int x = 0; x < SCREENW; x++)
//   {
//     int angle, distance;
//     float ratio = 32.0;
//     distance = int(ratio * texHeight / sqrt((x - w / 2.0) * (x - w / 2.0) + (y - h / 2.0) * (y - h / 2.0))) % texHeight;
//     angle = (unsigned int)(0.5 * texWidth * atan2(y - h / 2.0, x - w / 2.0) / 3.1416);
//     distanceTable[y][x] = distance;
//     angleTable[y][x] = angle;
//   }
// }

// void drawTunnel()
// {
//     for(int y = 0; y < SCREENH; y++)
//     for(int x = 0; x < SCREENW; x++)
//     {
//       //get the texel from the texture by using the tables, shifted with the animation values
//       int color = texture[(unsigned int)(distanceTable[y][x] + shiftX)  % texWidth][(unsigned int)(angleTable[y][x] + shiftY) % texHeight];
//       buffer[y][x] = color;
//     }
// }