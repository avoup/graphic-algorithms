#include<graphics.h>
#include<math.h>
using namespace std;

void serpinskiCarpet(double x = 250, double y = 250, double size = 500, int n = 4)
{
	setfillstyle(SOLID_FILL, COLOR(57, 255, 20));
	
	bar( x-ceil(size/6), y-ceil(size/6), x+floor(size/6), y+floor(size/6) );
	
	if (n == 1) return;

	serpinskiCarpet(x-size/3, y-size/3,  size/3, n-1); // top left
	serpinskiCarpet(x, 	      y-size/3,  size/3, n-1); // top middle
	serpinskiCarpet(x+size/3, y-size/3,  size/3, n-1); // top right
	
	serpinskiCarpet(x-size/3, y, 		 size/3, n-1); // middle left
	serpinskiCarpet(x+size/3, y, 		 size/3, n-1); // middle right
	
	serpinskiCarpet(x-size/3, y+size/3,  size/3, n-1); // bottom left
	serpinskiCarpet(x,		  y+size/3,  size/3, n-1); // bottom middle
	serpinskiCarpet(x+size/3, y+size/3,  size/3, n-1); // bottom right
}

int main()
{
	int depth = 4; // Depth of serpinski carpet
	double wSize = 500;
	
	initwindow(wSize, wSize);
	serpinskiCarpet(wSize/2, wSize/2, wSize - 10, depth);
		
	getch();	
	closegraph();
}



