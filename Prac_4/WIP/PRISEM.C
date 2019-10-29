#include <DOS.H>
#include "MAN_COLA.H"
#include "MAN_CPU.H"
#include "PRISEM.H"

void wait (int id) {
	disable();
	sem--;
	if(sem < 0) {
		sacar_cola_listos(id);
		meter_cola_semaforo(id);
		context_switch();
	}
	enable();
}

void signal(int id) {
	disable();
	sem++;
	if(sem <= 0) {
		sacar_cola_semaforo(id);
		meter_cola_listos(id);
		context_switch();
	}
	enable();
}

////////////////////////////////////////////////////////////////////////////////

void init_cola_semaforo() {
//	colaSem[10] = {0,0,0,0,0,0,0,0,0,0};
}

void init_semaforo(int cont){
	sem = cont;
	init_cola_semaforo();
}

void sacar_cola_semaforo(int id) {
	int i;
	for (i = 0; i < totalSem; i++) {
		if (colaSem[i] == id) {
			colaSem[i] = colaSem[i+1];
			id = colaSem[i+1];
		}
	}
	totalSem--;
}

void meter_cola_semaforo(int id) {
	colaSem[totalSem++] = id;
}
