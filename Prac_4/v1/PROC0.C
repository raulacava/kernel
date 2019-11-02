#include <DOS.H>
#include "PROC0.H"
#include "PRISEM.H"

void proc0() {
	int infty = 1;

	activa(&proc1, 1); // Editor
	activa(&proc2, 2); // Pelotita
//	activa(&proc3, 3); // Numeros
//	activa(&proc4, 4); // Hora
	activa(&proc5, 5); // Escritor
	activa(&proc6, 6); // Lector

//	init_semaforo(1);
	f = 0;
	elimina(0);

	while (infty);
}
