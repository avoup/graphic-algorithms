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
   	
   if (M < 0 ) return 1;
   return 0;
 }
 
void surface(Point light, int I, int K, double t = 0.1, double depth = 3.14/2, bool isInsideTriangle = true, bool isWavy = false) {
	
	if ( depth > 3.14/2 || depth < 0)
	{
		printf("depth should be between [0; pi/2]");
		return;
	}
	
	// Trianlge coords
    Point A[3];
	A[1].x = 50;  A[1].y = 50; A[1].z = 0;   
	A[0].x = 450; A[0].y = 50; A[0].z = 0;   
	A[2].x = 250; A[2].y = 450; A[2].z = 0;   
	
    // Draw triangle lines
    for (int i = 0; i < 3; i++)
		line(A[i].x, A[i].y, A[(i+1)%3].x, A[(i+1)%3].y );
   
	int minX = min(min(A[0].x, A[1].x), A[2].x);
	int minY = min(min(A[0].y, A[1].y), A[2].y);
	int maxX = max(max(A[0].x, A[1].x), A[2].x);
	int maxY = max(max(A[0].y, A[1].y), A[2].y);

	/**
	* Loop through all the points
	* and draw only inside triangle
	* and iluminate with lambertians reflectance
	*/
	for(int y = minY; y < maxY; y++)
	{		
		for(int x = minX; x < maxX; x++)
		{			
			Point curr = {x, y, 0};
			
			double distance = sqrt(pow(curr.x - light.x, 2) + pow(curr.y - light.y, 2) + pow(curr.z - light.z, 2));
			
			// Make waves on the surface
			if (isWavy) {
			
				double waveX = sin(x * t); // wave X
				double waveY = sin(y * t); 
				double wave = waveX * waveY * depth; // Calculate depth according to waves
				wave *= 25; // Make waves deeper looking
							
				// Add wave depth to a distance to calculate corresponding ilumination coeficient
				// This will give us increased angle between light ray and surface
				distance += wave;	
			}
				
			// Lambertian algorithm						
			double cos = light.z / distance;			
			double intensity = I * K * cos / pow(distance, 2);
			
			int r = 0, g = 0, b = 50;
			
			// Confine colors to 0-255 range
			r = (255 * intensity) + r > 255 ? 255 : (int) 255 * intensity + r;
			g = (255 * intensity) + g > 255 ? 255 : (int) 255 * intensity + g;
			b = (255 * intensity) + b > 255 ? 255 : (int) 255 * intensity + b;
						
			// Check if it should draw inside triangle
			if (isInsideTriangle) {
				// Calculate if point falls inside a triangle and draw if it does		
				int sum = side(A[0], A[1], curr) + side(A[1], A[2], curr) + side(A[2], A[0], curr);
				if (sum == 3 || sum == (0)) putpixel(x, y, COLOR(r, g, b));	
			} else {
				putpixel(x, y, COLOR(r, g, b));
			}
			
		}
	}
}
   
main ()  
 {
  
	Point light = {200, 250, 100};
	
	int I = 10000; // Light intensity
	int K = 1; // Reflection
	
	int width = 500;
	int height = 500;
	
	initwindow(width, height);   
	cleardevice();   
   
	surface(light, I, K, 0.1, 3.14/2, true, true); // Draw surface
    
	getch();  
	closegraph();
 }
