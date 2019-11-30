#include <DOS.H>
#include "PROCESO0.H"

void proceso0() {
	int infty = 1;

	activa(&proceso1, 1);
	activa(&proceso5, 5);
	activa(&proceso6, 6);
	//activa(&proceso3, 2);
	//activa(&proceso2, 3);
	activa(&proceso4, 4);


	elimina(0);

	while (infty);
}