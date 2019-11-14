// Envia
#include <CONIO.H>
#include <DOS.H>
#include <STRING.H>
#include "PROC0.H"
#include "PRISEM.H"

void proc7() {
	struct text_info initial_info;
	int xo, yo;
	int x, y;
	char msj[10][20] = {'m0','m1','m2','m3','m4','m5','m6','m7','m8','m9'};
//	string msj[10] = {"m0","m1","m2","m3","m4","m5","m6","m7","m8","m9"};
	int i;
	int p = 3;

	gettextinfo(&initial_info);
	xo = (p == 1 || p == 3) ? 0 : initial_info.screenwidth /2;
	yo = (p == 1 || p == 2) ? 0 : initial_info.screenheight/2;

	x = xo + 1;
	y = yo + 1;

	for (i = 0; i < 10 ;i++) {
		disable();
		gotoxy(x + 3 * i, y);
		printf("%s\n%d", msj[i], x + 3 * i);
		enable();
	}

	while (1) {
	}
}
