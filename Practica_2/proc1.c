/* Proceso 1
 * El Editor
 */
#include <graphics.h>
#include <conio.h>

#define ESC 27

int main() {
	char key;
	struct text_info initial_info;

	gettextinfo(&initial_info);

	clrscr();
	while (key != ESC) {
		key = getch();
		putch(key);
		if (wherex() >= initial_info.screenwidth)
			if (wherey() >= initial_info.screenheight)
				gotoxy(1, 1);
	}
	return 0;
}