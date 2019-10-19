#include <DOS.H>
#include "MAN_CPU.H"
#include "INIT.H"

void interrupt context_switch() {
	disable();

	pcbs[PtrRun->Este].ss = _SS;
	pcbs[PtrRun->Este].sp = _SP;

	g_bFirstRun = 0;

	if (++g_iTicks >= 18) {
		g_iTicks = 0;
		g_iSeconds++;
	}

	InsertaListos(PtrRun);   // siguiente proceso
	PtrRun = PrimeraTarea(); // asigna al siguiente en la cola

	_SS = pcbs[PtrRun->Este].ss;
	_SP = pcbs[PtrRun->Este].sp;
	gotoxy(g_iLastX,g_iLastY);
	old_clock();
	enable();
}
