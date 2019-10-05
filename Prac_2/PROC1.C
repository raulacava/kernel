/* Proceso 1
 * El Editor
 */
#include <graphics.h>
#include <conio.h>

#define ESC 27

int main() {
	int n;
	char key;
	struct text_info initial_info;
	int xo, yo;
	int p = 1;

	gettextinfo(&initial_info);
	xo = p == 1 || p == 3 ? 0 : initial_info.screenwidth /2;
	yo = p == 1 || p == 2 ? 0 : initial_info.screenheight/2;

//	clrscr();
	gotoxy(xo + 1, n = yo + 1);
	while (key != ESC) {
		key = getch();
		putch(key);
		if (wherex() >= xo + initial_info.screenwidth/2)
			if (wherey() >= yo + initial_info.screenheight/2)
				gotoxy(xo + 1, n = yo + 1);
			else gotoxy(xo + 1, ++n);
	}
	return 0;
}
