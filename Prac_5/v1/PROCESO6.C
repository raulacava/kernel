// Lector
#include <CONIO.H>
#include <DOS.H>
#include "MAN_BUZ.H"
#include "PROCESO0.H"
#include "PRINSEM.H"

void proceso6() {
	struct text_info initial_info;
	int xo, yo;
	int x, y;
	int i,j;
	//int B[10];
	int p = 4;
	char msj2receive[20];
	gettextinfo(&initial_info);
	xo = (p == 1 || p == 3) ? 0 : initial_info.screenwidth /2;
	yo = (p == 1 || p == 2) ? 0 : initial_info.screenheight/2;

	x = xo + 1;
	y = yo + 1;

	for (i = 0; i < 10 ;i++) {
		//wait();
		//disable(); //B[i] = var_global[i];
		disable(); gotoxy(x,y);	disable(); //printf("%2d", B[i]);

		recibe(msj2receive);
		disable();	printf("Recibe process: "); 
		printf("%s",msj2receive);
		disable(); gotoxy(x,y+1);	disable();
		disable();  printf("mensaje recibido: %d\n",i);
		enable(); 
		delay(2000);
		//for (j = 0; j < 10000 ;j++); 
		//signal();
	}

	while (1) {
		disable(); gotoxy(x, y + 11);
		disable(); printf("Termino recibe");
		enable();
	}
}
