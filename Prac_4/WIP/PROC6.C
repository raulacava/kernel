// Lector
#include <CONIO.H>
#include <DOS.H>
#include "PROC0.H"
#include "PRISEM.H"

void proc6() {
	struct text_info initial_info;
	int xo, yo;
	int x, y;
	int i;
	int B[10];
	int p = 4;

	gettextinfo(&initial_info);
	xo = (p == 1 || p == 3) ? 0 : initial_info.screenwidth /2;
	yo = (p == 1 || p == 2) ? 0 : initial_info.screenheight/2;

	x = xo + 1;
	y = yo + 1;

	for (i = 0; i < 10 ;i++) {
		wait();
		disable(); B[i] = var_global[i];
		disable(); gotoxy(x + 3 * i, y);
		disable(); printf("%2d", B[i]);
		enable();  delay(250);
		signal();
	}

	while (1) {
		disable(); gotoxy(x, y + 11);
		disable(); printf("Termino Lector");
		enable();
	}
}
