#include <DOS.h>
#include "INIT.H"
#include "MAN_COLA.H"
#include "MAN_CPU.H"

void interrupt context_switch()
{
	disable();
	/* salva la pila del proceso en ejecucion */
	pcbs[PtrRun->Este].ss = _SS;
	pcbs[PtrRun->Este].sp = _SP;


	g_bFirstRun = 0;

	/* incrementa la variable 'g_iSeconds' cada 18 interrupciones (cada segundo) */

	if (++g_iTicks >= 18) {

		g_iTicks = 0;
		g_iSeconds++;
	}

    InsertaListos(PtrRun);

    PtrRun = PrimeraTarea();

	/* apunta al siguiente proceso en la fila de procesos */

	// g_iActualProcess = (g_iActualProcess + 1) % g_iNumProcesses;

	/* cambia la pila por la del nuevo proceso en ejecucion */

	_SS = pcbs[PtrRun->Este].ss;
	_SP = pcbs[PtrRun->Este].sp;
	gotoxy(g_iLastX,g_iLastY);
	(*old_clock)();
	enable();
}