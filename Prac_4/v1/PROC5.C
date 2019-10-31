// Escritor
#include <CONIO.H>
#include <DOS.H>
#include "PROC0.H"
#include "PRISEM.H"
#include "MAN_COLA.H"

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
		wait(5);
		disable(); var_global[i] = A[i];
		disable(); gotoxy(x + 3 * i, y);
		disable(); printf("%2d", A[i]);
//		disable(); printf("%2d\n%2d", A[i], var_global[i]);
		enable();  delay(250);
		signal(5);
	}
//	while (1) {
		disable(); gotoxy(x, y + 11);
		disable(); printf("Termino Escritor.");
		enable();
//	}
	elimina(curr);
}
