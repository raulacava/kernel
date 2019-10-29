#include "PRISEM.H"

void wait (int id) {
	disable();
	s[id].valor--;
	if(s[id].valor < 0){
		sacar_cola_listos(id);
		meter_cola_semaforo(id);
		context_switch();
	}
	enable();
}

void signal(int id) {
	disable();
	s[id].valor++;
	if(s[id].valor<=0){
		sacar_cola_semaforo(id);
		meter_cola_listo(id);
		cambio_contexto();
	}
	enable();
}

void init_cola_semaforo() {
	colaSem[10];
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
