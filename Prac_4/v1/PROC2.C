// Pelotita
#include <CONIO.H>
#include <DOS.H>
#include "PROC0.H"

void proc2() {
	int x, y;
	int xs = 1, ys = 1;
	char key = 'o';
	struct text_info initial_info;
	int xo, yo;
	int p = 2;

	gettextinfo(&initial_info);
	xo = p == 1 || p == 3 ? 0 : initial_info.screenwidth /2;
	yo = p == 1 || p == 2 ? 0 : initial_info.screenheight/2;

	x = xo + 1;
	y = yo + 1;

	// clrscr();
	while (infty) {
		if (kbhit()) key = getch();
		if (key == ESC) {
			isOn = 0;
			infty  = 0;
		}
		disable(); gotoxy(x, y);
		disable(); putch('o');
		disable(); gotoxy(xo + 1, yo + 1);
		 enable(); delay(100);
		disable(); gotoxy(x, y);
		disable(); putch(' ');
		 enable();
		x += xs;
		y += ys;
		if (x >= xo + initial_info.screenwidth /2 || x <= xo + 1) xs = -xs;
		if (y >= yo + initial_info.screenheight/2 || y <= yo + 1) ys = -ys;
	}
}
