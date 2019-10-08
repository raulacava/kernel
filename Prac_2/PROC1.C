/* Proceso 1
 * El Editor
 */
#include <conio.h>
#include <dos.h>

#define ESC 27

int main() {
	struct text_info initial_info;
	int x, y, xo, yo;
	char key;
	int p = 1;

	gettextinfo(&initial_info);
	xo = p == 1 || p == 3 ? 0 : initial_info.screenwidth /2;
	yo = p == 1 || p == 2 ? 0 : initial_info.screenheight/2;

//	clrscr();
	x = xo + 1;
	y = yo + 1;
	while (key != ESC) {
		key = getch();
//		disable();
		gotoxy(x, y);
		putch(key);
//		enable();
		if (x++ >= xo + initial_info.screenwidth/2) {
			x = xo + 1;
			if (y++ >= yo + initial_info.screenheight/2) {
				y = yo + 1;
			}
		}
	}
	return 0;
}
