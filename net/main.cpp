#include<graphics.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;

struct coord2D 
{
	double x, y;
};
struct coord3D
{
	double x, y, z;
};
struct coordSystem
{
	int X0, Y0;
	double alpha;
};

// Calculate 3d point coordinates on 2d plane
coord2D calculate2DPoint(coordSystem base, coord3D p)
{
	return coord2D {
		base.X0 + p.x + p.z*cos(base.alpha),
		base.Y0 - p.y - p.z*sin(base.alpha),
	};
}

// Draw 3d point coordinates on 2d plane
void drawPixel3D(coordSystem base, coord3D p, int color)
{
	coord2D d = calculate2DPoint(base, p);
	putpixel(d.x, d.y, color);
}

// Draw line 3d
void drawLine3D(coordSystem base, coord3D p0, coord3D p1, int color, short style = 0, short width = 1)
{
	int x0, y0, x1, y1;

	x0 = base.X0 + p0.x + p0.z*cos(base.alpha);
	y0 = base.Y0 - p0.y - p0.z*sin(base.alpha);
	
	x1 = base.X0 + p1.x + p1.z*cos(base.alpha);
	y1 = base.Y0 - p1.y - p1.z*sin(base.alpha);
	
	setcolor(color);	
	setlinestyle(style, 0, width);
	line (x0, y0, x1, y1);
};

// Draw XYZ axises
void drawCoordSystem (coordSystem base, int size) 
{		
	coord3D p0  = {0,    0,    0};
	coord3D p1x = {size, 0,    0};
	coord3D p1y = {0,    size, 0};
	coord3D p1z = {0,    0,    -size};
	
	drawLine3D ( base, p0, p1x, RED,   1, 3 );
	drawLine3D ( base, p0, p1y, GREEN, 1, 3 );
	drawLine3D ( base, p0, p1z, BLUE,  1, 3 );
};

/**
* Draw sine wave net 3D
*/
void net (coordSystem base, double increment)
{
	double p = 3.14;
	double np = -3.14;
	int scale = 50;
	double scaledI = 1.0 / scale;
	increment = p / (increment/2);
	
	for(double T = np; T < p; T+=increment)
	{			
		for(double t = np; t < p; t+= scaledI){
			double x_y = sin(t) + sin(T);
			double z_y = x_y;
			
			coord3D x_p =  {scale * t, scale * x_y, scale * T};
			coord3D z_p =  {scale * T, scale * z_y, scale * t};
						
			int r = int((256 + 255 * (x_y / 2)) / 2 );
			int g = int((256 + 255 * (x_y / 2)) / 2 );
			int b = 255 - int((256 + 255 * (x_y / 2)) / 2 );
			
			drawPixel3D(base, x_p,  COLOR(r, g, b));
			drawPixel3D(base, z_p,  COLOR(r, g, b));
		}				
	}
		
}


int main()
{
	
	int w = 800;
	int h = 800;
	double a = 0.4; // View angle
	
	initwindow(w, h);
	cleardevice();	
	
	coordSystem base = {w/2, h/2, a}; // base point for coordinate system
	drawCoordSystem(base, 300); // draw coordinate system	
	
	net(base, 70); // Draw sine wave net 3D
	
	getch();	
	closegraph();
}

