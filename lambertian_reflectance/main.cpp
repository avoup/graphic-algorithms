#include<iostream>
#include<math.h>
#include<graphics.h>
using namespace std;
  
struct Point
{
	int x, y, z;
};

int side(Point P0, Point P1, Point C)
 {
   double M = (C.y-P0.y)*(P1.x-P0.x) - (C.x-P0.x)*(P1.y-P0.y);
   	
   if (M > 0) return 1;
   return 0;
 }
   
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
   
   // trianlge coords
    Point A[3];
	A[0].x = 50; A[0].y = 50; A[0].z = 0;   
	A[1].x = 450; A[1].y = 50; A[1].z = 0;   
	A[2].x = 250; A[2].y = 450; A[2].z = 0;   
	
    // draw triangle lines
    for (int i = 0; i < 3; i++)
		line(A[i].x, A[i].y, A[(i+1)%3].x, A[(i+1)%3].y );
   
//	int minX = min(min(A[0].x, A[1].x), A[2].x);
//	int minY = min(min(A[0].y, A[1].y), A[2].y);
//	int maxX = max(max(A[0].x, A[1].x), A[2].x);
//	int maxY = max(max(A[0].y, A[1].y), A[2].y);
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
			
			int sum = side(A[0], A[1], curr) + side(A[1], A[2], curr) + side(A[2], A[0], curr);
						
//			if (sum == 3 || sum == 0) putpixel(x, y, COLOR(r, g, b));
			putpixel(x, y, COLOR(r, g, b));
		}
	}
    
  	getch();  
 	closegraph();
 }
