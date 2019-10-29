// Escritor
#include <CONIO.H>
#include "PROC0.H"
#include "PRISEM.H"

void proc5() {
	struct text_info initial_info;
	int xo, yo;
	int x, y;
	int i;
	int A[10] = {1,2,3,5,7,11,13,17,19,23};
	int p = 3;

	gettextinfo(&initial_info);
	xo = (p == 1 || p == 3) ? 0 : initial_info.screenwidth /2;
	yo = (p == 1 || p == 2) ? 0 : initial_info.screenheight/2;

	x = xo + 1;
	y = yo + 1;

	for (i = 0; i < 10 ;i++) {
//		wait(0);
		var_global[i] = A[i];
		gotoxy(x + 3 * i, y);     printf("%2d", A[i]);          delay(500);
//		gotoxy(x + 3 * i, y +1 ); printf("%2d", var_global[i]); delay(500);
//		signal(0);
	}

	while (1) {
		gotoxy(x, y + 11);
		printf("Termino Escritor.");
	}
}
