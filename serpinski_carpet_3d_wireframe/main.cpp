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

coord2D calculate2DPoint(coordSystem base, coord3D p)
{
	return coord2D {
		base.X0 + p.x + p.z*cos(base.alpha),
		base.Y0 - p.y - p.z*sin(base.alpha),
	};
}

void drawPixel3D(coordSystem base, coord3D p, int color)
{
	coord2D d = calculate2DPoint(base, p);
	putpixel(d.x, d.y, color);
}

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

void drawCube(coordSystem base, coord3D start, int size = 150, int style = 0, int color = WHITE, int border = 1)
{	
	// vertices
	coord3D p0  = {start.x,        start.y,        start.z};
	coord3D p1x = {start.x + size, start.y,        start.z};
	coord3D p1y = {start.x,        start.y + size, start.z};
	coord3D p1z = {start.x,        start.y,        start.z-size};
	
	coord3D p1xy  = {start.x + size, start.y + size, start.z};
	coord3D p1xyz = {start.x + size, start.y + size, start.z - size};
	coord3D p1yz  = {start.x,        start.y + size, start.z - size};	
	coord3D p1xz  = {start.x + size, start.y,        start.z - size};
	
	// draw lines between vertices
	drawLine3D ( base, p0,    p1x,  color, style, border );
	drawLine3D ( base, p0,    p1y,  color, style, border );
	drawLine3D ( base, p0,    p1z,  color, style, border );
	
	drawLine3D ( base, p0,    p1x,  color, style, border );
	drawLine3D ( base, p0,    p1y,  color, style, border );
	drawLine3D ( base, p1xyz, p1yz, color, style, border );	
	drawLine3D ( base, p1xyz, p1xy, color, style, border );
	drawLine3D ( base, p1xyz, p1xz, color, style, border );
	
	drawLine3D ( base, p1y,   p1xy, color, style, border );
	drawLine3D ( base, p1y,   p1yz, color, style, border );
	
	drawLine3D ( base, p1x,   p1xy, color, style, border );
	drawLine3D ( base, p1x,   p1xz, color, style, border );
	drawLine3D ( base, p1z,   p1yz, color, style, border );
	drawLine3D ( base, p1z,   p1xz, color, style, border );
}

void drawRecurringCube(coordSystem base, double size = 150, int color = WHITE, int depth = 1)
{
	short style = 0; // solid lines
	short cubes = 9; // number of child cubes
	
	int r, g, b;
	r = depth * 10;
	g = depth * 50;
	b = depth * 100;
		
	drawCube( base, coord3D {0, 0, 0}, size, style, color, depth * 2 ); // draw cube
	
	if (depth == 0) return;
	
	// children cubes
	for (int i = 0; i < cubes; i++)
	{			
		// draw 3 cubes per iteration
		double x, y, z;
		
		x = 0;
		y = size/3 * (i % 3);
		z = -size/3 * floor(i / 3);
		
		if (y != -z || y != size/3) // check if cube is not centered in x = 0 plane
		{
			coord2D p0 = calculate2DPoint(base, coord3D {x, y, z}); // calculate 2d point from current cube coords
			coordSystem c0 = {p0.x, p0.y, base.alpha}; // new coordinate system for cube
			drawRecurringCube(c0, size/3, COLOR(r, g, b), depth - 1);
		}
		
		x = size/3;
		if (x != y && x != -z) // check if cube is not centered in x = size/3 plane
		{			
			coord2D p1 = calculate2DPoint(base, coord3D {x, y, z});
			coordSystem c1 = {p1.x, p1.y, base.alpha};
			drawRecurringCube(c1, size/3, COLOR(r, g, b), depth - 1);
		}
		
		x = 2*x;		
		if (y != -z || y != size/3) // check if cube is not centered in x = 2*size/3 plane
		{
		coord2D p2 = calculate2DPoint(base, coord3D {x, y, z});
		coordSystem c2 = {p2.x, p2.y, base.alpha};		
		drawRecurringCube(c2, size/3, COLOR(r, g, b), depth - 1);		
		}
	}
	
}

int main()
{
	int w = 700;
	int h = 700;
	double a = 0.4;
	coordSystem base = {w/2, h/2, a}; // base point for coordinate system
		
	initwindow(w, h);
	cleardevice();
	
	double alpha = a;
	
	do
	{
		cleardevice();		
		
		drawCoordSystem(coordSystem {base.X0, base.Y0, alpha}, 300); // draw coordinate system	
	
		drawRecurringCube(base, 300, WHITE, 1); // 3d wireframe serpinski carpet
	
		alpha += alpha;		
	
	} while(false); // true to rotate


	getch();	
	closegraph();
}
