// Escritor
#include <CONIO.H>
#include <DOS.H>
#include "MAN_BUZ.H"
#include "PROC0.H"
#include "PRISEM.H"

void proc5() {
	struct text_info initial_info;
	int xo, yo;
	int x, y;
	long int i, j;
	int A[10] = {1,2,3,5,7,11,13,17,19,23};
	//char msj2send[10][20] = {'u0','m1','m2','m3','m4','m5','m6','m7','m8','m9'}; 
	char msj2send[1];
	int p = 3;

	gettextinfo(&initial_info);
	xo = (p == 1 || p == 3) ? 0 : initial_info.screenwidth /2;
	yo = (p == 1 || p == 2) ? 0 : initial_info.screenheight/2;

	x = xo + 1;
	y = yo + 1;
	//clrscr();
	for (i = 0; i < 10 ;i++) {
		//wait();
		//disable(); //var_global[i] = A[i];
		//disable(); gotoxy(x + 3 * i, y);
		//disable(); //printf("%2d\n%2d", A[i], var_global[i]);
		            
	     sprintf(msj2send, "%d", i);
		 envia(msj2send);
		//disable();  printf("mensaje: %d",i);
		          
		//enable(); 
		for (j = 0; j < 1000000 ;j++);
		//signal();
	}

	while (1) {
		disable(); gotoxy(x, y + 11);
		disable(); printf("Termino envio.");
		enable();
	}
}
