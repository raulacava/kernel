// Hora
#include <CONIO.H>
#include <STDIO.H>
#include <DOS.H>
#include "PROC0.H"

void proc4() {
	struct text_info initial_info;
	struct time now;
	int x, y, xo, yo;
	char key;
	unsigned char s = 60;
	int p = 4;

	gettextinfo(&initial_info);
	xo = p == 1 || p == 3 ? 0 : initial_info.screenwidth /2;
	yo = p == 1 || p == 2 ? 0 : initial_info.screenheight/2;

	x = initial_info.screenwidth /4 - 4;
	y = initial_info.screenheight/4;

	// clrscr();
	while (infty) {
		if (kbhit()) key = getch();
		if (key == ESC) {
			isOn = 0;
			infty  = 0;
		}
		gettime(&now);
		if (s != now.ti_sec) {
			disable(); gotoxy(xo + x, yo + y);
			disable(); printf("%02d:%02d:%02d", 
				now.ti_hour, 
				now.ti_min, 
				now.ti_sec);
			enable();
			s = now.ti_sec;
		}
	}
}
