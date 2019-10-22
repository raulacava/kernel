#include <DOS.H>
#include "INIT.H"     // pcbs
#include "MAN_COLA.H" // PtrRun, InsertaListos(), PrimeraTarea()
#include "MAN_CPU.H"  // g_bFirstRun, g_iTicks, g_iSeconds, g_iLastX, g_iLastY, context_switch()

void interrupt context_switch() {
	disable();

	DD[PtrRun->Este].ss = _SS;
	DD[PtrRun->Este].sp = _SP;

	InsertaListos(PtrRun);   // siguiente proceso
	PtrRun = PrimeraTarea(); // asigna al siguiente en la cola

	_SS = DD[PtrRun->Este].ss;
	_SP = DD[PtrRun->Este].sp;
	(*old_clock)();
	enable();
}
