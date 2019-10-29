#include <DOS.H>
#include "INIT.H"     // 
#include "MAN_COLA.H" // 
#include "MAN_CPU.H"  // 
#include "PROC0.H"

int cuenta = 0;

void interrupt context_switch() {
	disable();

//	pushes(_SS, _SP);
	if (f) {
		DD[curr].ss = _SS;
		DD[curr].sp = _SP;
	}
	else f = 1;

	// siguiente en la cola
	primero_cola_listos();

	(*old_clock)();

//	popes();
 	_SS = DD[next].ss;
 	_SP = DD[next].sp;

//	disable(); gotoxy((cuenta++%79)+1, 25);
//	disable(); gotoxy(1, 25);
//	disable(); printf("%d", isOn);
	enable();
}

////////////////////////////////////////////////////////////////////////////////
// void pushes(unsigned a, unsigned b) {
// 	if (f) {
// 		DD[cola[indice]].ss = a;
// 		DD[cola[indice]].sp = b;
// 	}
// 	else f = 1;
// }

// void popes() {
// 	_SS = DD[cola[indice]].ss;
// 	_SP = DD[cola[indice]].sp;
// }
