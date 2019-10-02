/* Proceso 1
 * La Bolita
 */
#include <graphics.h>
#include <conio.h>

#define ESC 27

int main() {
	int x, y;
	int xs = 1, ys = 1;
	char key = 'o';
	struct text_info initial_info;
	int xo, yo;

	gettextinfo(&initial_info);
//	xo = 0; yo = 0;
	xo = initial_info.screenwidth /2; yo = 0;
//	xo = 0; yo = initial_info.screenheight/2;
//	xo = initial_info.screenwidth /2; yo = initial_info.screenheight/2;

	x = xo + 1;
	y = yo + 1;

	clrscr();
	while (key != ESC) {
		if (kbhit()) key = getch();
		disable();
		gotoxy(x, y);
		putch(key);
		gotoxy(xo + 1, yo + 1);
		enable();
		delay(100);
		disable();
		gotoxy(x, y);
		putch(' ');
		enable();
		x += xs;
		y += ys;
		if (x >= xo + initial_info.screenwidth /2 || x <= xo + 1) xs = -xs;
		if (y >= yo + initial_info.screenheight/2 || y <= yo + 1) ys = -ys;
	}
	return 0;
}
