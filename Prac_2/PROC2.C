/* Proceso 2
 * La Pelotita
 */
#include <dos.h>
#include <conio.h>

#define ESC 27

int main() {
	struct text_info initial_info;
	int x, y, xo, yo;
	char key = 'o';
	int xs = 1, ys = 1;
	int p = 2;

	gettextinfo(&initial_info);
	xo = p == 1 || p == 3 ? 0 : initial_info.screenwidth /2;
	yo = p == 1 || p == 2 ? 0 : initial_info.screenheight/2;

	x = xo + 1;
	y = yo + 1;

//	clrscr();
	while (key != ESC) {
		if (kbhit()) key = getch();
//		disable();
		gotoxy(x, y);
		putch('o');
		gotoxy(xo + 1, yo + 1);
//		enable();
		delay(100);
//		disable();
		gotoxy(x, y);
		putch(' ');
//		enable();
		x += xs;
		y += ys;
		if (x >= xo + initial_info.screenwidth /2 || x <= xo + 1) xs = -xs;
		if (y >= yo + initial_info.screenheight/2 || y <= yo + 1) ys = -ys;
	}
	return 0;
}
