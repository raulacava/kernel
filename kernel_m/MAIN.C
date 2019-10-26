#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "MAIN.H"
#include "INIT.H"
#include "MAN_COLA.H"
#include "MAN_CPU.H"
#include "DATOS.H"

int main()
{
	int bContinuerWhile = 1;
	clrscr();
	//inicializa procesos
	init_process(&proceso1, 0);
	init_process(&proceso3, 1);
	init_process(&proceso2, 2);
	init_process(&proceso4, 3);
	g_iActualProcess = 0;
	init_system();
	while(bContinuerWhile);
	term_system();
	printf("press any key to continue\n");
	getch();
	return 0;
}
