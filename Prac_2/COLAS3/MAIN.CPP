#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "DATOS.H"

int main() {
	g_iActualProcess = g_iNumProcesses = g_iTicks = g_iSeconds = 0;
	g_bFirstRun = 1;
	g_iLastY = g_iLastX = 0;
	int bContinuerWhile = 1;

	clrscr();

	init_process(&proc1, 1);
	init_process(&proc2, 2);
	init_process(&proc3, 3);
	init_process(&proc4, 4);

	g_iActualProcess = 0;

	old_clock = getvect(CLK_INT);

	setvect(CLK_INT, context_switch);

	while(bContinuerWhile);

	setvect(CLK_INT, old_clock);

	printf("press any key to continue\n");
	getch();
	return 0;
}
