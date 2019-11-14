#include <DOS.H>
#include "PROC0.H"
#include "PRISEM.H"

void proc0() {
	int infty = 1;

	activa(&proc1, 1);
	activa(&proc2, 2);
//	activa(&proc3, 3);
//	activa(&proc4, 4);
//	activa(&proc5, 5);
//	activa(&proc6, 6);
	activa(&proc7, 7);
	activa(&proc8, 8);

//	init_semaforo(1);
	f = 0;

	elimina(0);

	while (infty);
}
