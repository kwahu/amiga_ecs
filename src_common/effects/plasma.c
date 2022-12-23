//https://lodev.org/cgtutor/plasma.html

// void drawPlasma()
// {
//       for(int y = 0; y < h; y++)
//   for(int x = 0; x < w; x++)
//   {
//     int color = int(128.0 + (128.0 * sin(x / 8.0)));
//     pset(x, y, ColorRGB(color, color, color));
//   }
// }


//  for(int y = 0; y < h; y++)
//   for(int x = 0; x < w; x++)
//   {
//     int color = int(128.0 + (128.0 * sin(sqrt((x - w / 2.0) * (x - w / 2.0) + (y - h / 2.0) * (y - h / 2.0)) / 8.0)));
//     pset(x, y, ColorRGB(color, color, color));
//   }


//     for(int y = 0; y < h; y++)
//   for(int x = 0; x < w; x++)
//   {
//     int color = int
//     (
//         128.0 + (128.0 * sin(x / 8.0))
//       + 128.0 + (128.0 * sin(y / 8.0))
//     ) / 2;
//     pset(x, y, ColorRGB(color, color, color));
//   }