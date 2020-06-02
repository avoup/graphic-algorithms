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

// calculate 3d point coordinate on 2d plane
coord2D calculate2DPoint(coordSystem base, coord3D p)
{
	return coord2D {
		base.X0 + p.x + p.z*cos(base.alpha),
		base.Y0 - p.y - p.z*sin(base.alpha),
	};
}

// draw 3d coordinate on 2d plane
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

// draw 3d bezier curve with projections
void bezier3D (coordSystem base, coord3D points[], double increment)
{
	for(double t = 0; t <= 1; t += increment)
	{
		double x = points[0].x*pow((1-t), 3) + 3*points[1].x*pow((1-t), 2)*t + 3*points[2].x*(1-t)*t*t + points[3].x*t*t*t;
		double y = points[0].y*pow((1-t), 3) + 3*points[1].y*pow((1-t), 2)*t + 3*points[2].y*(1-t)*t*t + points[3].y*t*t*t;
		double z = points[0].z*pow((1-t), 3) + 3*points[1].z*pow((1-t), 2)*t + 3*points[2].z*(1-t)*t*t + points[3].z*t*t*t;
		
		coord3D p =  {x, y, z};
		coord3D px = {0, y, z};
		coord3D py = {x, 0, z};
		coord3D pz = {x, y, 0};
						
		drawPixel3D(base, p,  COLOR(220, 220, 220));
		drawPixel3D(base, px, COLOR(120, 120, 20)); // no X
		drawPixel3D(base, py, COLOR(120, 20, 120)); // no Y
		drawPixel3D(base, pz, COLOR(20, 120, 120));	// no Z
		
//		cout << t << endl;

//		if ( t == 0.03 )
//		{
//			cout << "meh" << endl;
//			drawLine3D(base, p, px, COLOR(0, 200, 200));
//			drawLine3D(base, p, py, COLOR(200, 0, 200));
//			drawLine3D(base, p, pz, COLOR(200, 200, 0));
//		}
	}
}


int main()
{
	
	int w = 800;
	int h = 800;
	double a = 0.4;
	
	initwindow(w, h);
	cleardevice();	
	
	coordSystem base = {w/2, h/2, a}; // base point for coordinate system
	drawCoordSystem(base, 300); // draw coordinate system	
	
	coord3D points[4];
	points[0] = {100, 20, -50};
	points[1] = {200, 120, -100};
	points[2] = {80, 160, -180};
	points[3] = {150, 50, -210};
	
	bezier3D(base, points, 0.001); 
	
	getch();	
	closegraph();
}

