#include <DOS.h>
#include "INIT.H"
#include "MAN_COLA.H"
#include "MAN_CPU.H"
#include "PROCESO0.H"
int cuenta = 0;
void interrupt context_switch()
{
	disable();
	if (f) {
		DD[curr].ss = _SS;
		DD[curr].sp = _SP;
	}
	else f = 1;

	primero_cola_listos();

	(*old_clock)();
	/* apunta al siguiente proceso en la fila de procesos */

	// g_iActualProcess = (g_iActualProcess + 1) % g_iNumProcesses;

	/* cambia la pila por la del nuevo proceso en ejecucion */

	_SS = DD[next].ss;
 	_SP = DD[next].sp;
	//gotoxy(g_iLastX,g_iLastY);
	//(*old_clock)();
	enable();
}