#include<iostream>
#include<math.h>
#include<graphics.h>
using namespace std;
  
struct Point
{
	int x, y, z;
};
   
main ()  
 {
  
  // light source's coordinates
   Point light = {200, 250, 100};
   
   int I = 10000; // light intensity
   int k = 1; // reflection
   
   int width = 400;
   int height = 400;

   initwindow(width, height);   
   cleardevice();   

	int minX = 0;
	int minY = 0;
	int maxX = width;
	int maxY = height;

	for(int y = minY; y < maxY; y++)
	{		
		for(int x = minX; x < maxX; x++)
		{			
			Point curr = {x, y, 0};
			
			// distance between light and current point
			double distance = sqrt(pow(curr.x - light.x, 2) + pow(curr.y - light.y, 2) + pow(curr.z - light.z, 2));
			
			// cos (sin in this case)
			double cos = light.z / distance;

			// lambert algorithm
			double intensity = I * k * cos / pow(distance, 2);
			
			int r = 0, g = 0, b = 50;
			
			// confine colors to 0-255 range
			r = (255 * intensity) + r > 255 ? 255 : (int) 255 * intensity + r;
			g = (255 * intensity) + g > 255 ? 255 : (int) 255 * intensity + g;
			b = (255 * intensity) + b > 255 ? 255 : (int) 255 * intensity + b;

			putpixel(x, y, COLOR(r, g, b));
		}
	}
    
  	getch();  
 	closegraph();
 }
