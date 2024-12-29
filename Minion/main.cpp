#include<graphics.h>
#include<conio.h>

#define KUZI_COLOR RGB(22, 96, 132)

#define PI 3.14
int main()
{
	int x = 300;
	int y = 400;
		
	initgraph(600, 800);
	setbkcolor(WHITE);
	cleardevice();

	setfillcolor(BLACK);
	solidrectangle(x - 50, y +150,x-20,y+340 );
	solidrectangle(x + 50, y + 150, x + 20, y + 340);
	solidcircle(x - 100, y + 320, 20);
	solidcircle(x + 100, y + 320, 20);
	POINT ps_l[] = {
		{x - 100,y + 300},
		{x - 50,y + 310},
		{x - 50,y + 340},
		{x - 100,y + 340}
	};
	POINT ps_r[] = {
	{x + 100,y + 300},
	{x + 50,y + 310},
	{x + 50,y + 340},
	{x + 100,y + 340}
	};
	solidpolygon(ps_l,4);
	solidpolygon(ps_r, 4);

	setfillcolor(YELLOW);
	solidcircle(x,y-150, 150);

	setfillcolor(KUZI_COLOR);
	solidcircle(x, y + 150, 150);
	setfillcolor(YELLOW);
	solidrectangle(x - 150, y - 150, x + 150, y + 150);
	
	setfillcolor(KUZI_COLOR);
	
	solidrectangle(x - 100, y + 100, x + 100, y + 150);
	POINT pts_l[] = { {x - 150,y + 20},
		{x - 96,y + 100},
		{x - 100,y + 108},
		{x - 150,y + 30} };
	POINT pts_r[] = { {x + 150,y + 20},
		{x + 96,y + 100},
		{x + 100,y + 108},
		{x + 150,y + 30} };
	solidpolygon(pts_l, 4);
	solidpolygon(pts_r, 4);
	setfillcolor(BLACK);
	// 
	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	setfillcolor(YELLOW);
	POINT s_l[] = {
		{x - 150,y + 50},
		{x - 150,y + 150},
		{x - 180,y + 125}
	};
	POINT s_r[] = {
		{x + 150,y + 50},
		{x + 150,y + 150},
		{x + 180,y + 125}
	};
	fillpolygon(s_l, 3);
	fillpolygon(s_r, 3);
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 8);
	fillcircle(x - 50, y - 150, 50);
	fillcircle(x + 50, y - 150, 50);

	setfillcolor(BLACK);
	solidcircle(x - 150, y - 150, 5);
	solidcircle(x + 150, y - 150, 5);
	solidrectangle(x - 150, y - 150 - 5, x - 100, y - 150 + 5);
	solidrectangle(x + 150, y - 150 - 5, x + 100, y - 150 + 5);

	solidcircle(x - 50 - 10, y - 150, 25);
	solidcircle(x + 50 - 10, y - 150, 25);
	setfillcolor(WHITE);
	solidcircle(x - 50 - 5, y - 150, 10);
	solidcircle(x + 50 - 5, y - 150, 10);

	setlinecolor(RED);
	arc(x - 50, y - 50, x + 50, y + 50, -PI,0);
	

	_getch(); 
	closegraph();


}