#include<graphics.h>
#include<math.h>
#include<conio.h>


#define PI 3.14159265359

void pentagram(int x,int y,int radius,double angle)
{
	POINT pts[5];
	double a = PI / 2;
	for (int i = 0; i < 5; i++) {
		pts[i].x = int(x + cos(a + angle) * radius);
		pts[i].y = int(y - sin(a + angle) * radius);
		a += PI * 4 / 5;
	}
	setpolyfillmode(WINDING);
	setfillcolor(YELLOW);
	solidpolygon(pts, 5);
}


int main()
{
	int width = 900;
	int height;
	int cell = width / 30;
	height = width / 3 * 2;

	initgraph(width,height);
	setbkcolor(RED);
	cleardevice();

#ifdef DEBUG
	for (int i = 0; i < 11; i++) {
		line(0, i * cell, width / 2, i * cell);
}
	for (int i = 0; i < 16; i++) {
		line(i * cell, 0, i * cell, height / 2);
	}

	line(5 * cell, 5 * cell, 10 * cell, 2 * cell);
	line(5 * cell, 5 * cell, 12 * cell, 4 * cell);
	line(5 * cell, 5 * cell, 12 * cell, 7 * cell);
	line(5 * cell, 5 * cell, 10 * cell, 9 * cell);
#endif // DEBUG

	pentagram(5 * cell, 5 * cell, 3 * cell, 0);
	pentagram(10 * cell, 2 * cell, cell, PI - atan(5.0 / 3.0));
	pentagram(12 * cell, 4 * cell, cell, PI - atan(7.0 / 1.0));
	pentagram(12 * cell, 7 * cell, cell, atan(7.0 / 2.0));
	pentagram(10 * cell, 9 * cell, cell, atan(5.0 / 4.0));

	_getch();
	closegraph();
	return 0;
}