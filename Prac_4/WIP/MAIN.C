#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "INIT.H"
#include "PROC0.H"
#include "MAN_COLA.H"
#include "MAN_CPU.H"
#include "DATOS.H"

int main() {
	clrscr();

	init_system();

	while (isOn);
	infty = 0;

	term_system();

	enable();
	gotoxy(1, 25); printf("Press any key to exit...");
	getch();
	return 0;
}
