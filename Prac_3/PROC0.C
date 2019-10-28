#include <DOS.H>
#include "PROC0.H"

void proc0() {
	int infty = 1;

	activa(&proc1, 1);
	activa(&proc2, 2);
	activa(&proc3, 3);
	activa(&proc4, 4);

	elimina(0);

	while (infty);
}
