#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "MAIN.H"
#include "INIT.H"
#include "MAN_COLA.H"
#include "MAN_CPU.H"
#include "MAN_BUZ.H"
#include "DATOS.H"
#include "PROCESO0.H"

int main()
{
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
