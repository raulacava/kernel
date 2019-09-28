#include <graphics.h>
#include <conio.h>

#define ESC 27

int main() {
	int x = 1, y = 1;
	char key;
	struct text_info initial_info;
	gettextinfo(&initial_info);

	clrscr();
	while (key != ESC) {
		key = getch();
		gotoxy(x, y);
		printf("%c", key);
		if (x++ >= initial_info.screenwidth) {
			x = 1;
			if (y++ >= initial_info.screenheight) {
				y = 1;
			}
		}
	}

	return 0;
}
