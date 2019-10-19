#include <CONIO.H>
#include <DOS.H>

#define ESC 27

void proc1() {
	int x, y;
	char key;
	struct text_info initial_info;
	int xo, yo;
	int p = 1;

	gettextinfo(&initial_info);
	xo = (p == 1 || p == 3) ? 0 : initial_info.screenwidth /2;
	yo = (p == 1 || p == 2) ? 0 : initial_info.screenheight/2;

	// clrscr();
	x = xo + 1;
	y = yo + 1;
	while (key != ESC) {
		key = getch();
		disable();
		gotoxy(x, y);
		putch(key);
		enable();
		if (x++ >= xo + initial_info.screenwidth/2) {
			x = xo + 1;
			if (y++ >= yo + initial_info.screenheight/2) {
				y = yo + 1;
			}
		}
	}
}
