#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "MAIN.H"
#include "INIT.H"
#include "MAN_COLA.H"
#include "MAN_CPU.H"
#include "DATOS.H"

int main() {
	unsigned temp = 1;
	clrscr();

	init_process(&proc1, 1);
	init_process(&proc2, 2);
	init_process(&proc3, 3);
	init_process(&proc4, 4);

	init_system();

	while(temp);

	term_system();

	printf("Press any key to exit.\n");
	getch();
	return 0;
}
