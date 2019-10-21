#include "datos.h"

int cola[10];
int total = 0;
int indice = -1;

void meter_cola_listos(int id) {
	cola[total++] = id;
}

void sacar_cola_listos(int id) {
	int i;
	for (i = 0; i < total; i++) {
		if (cola[i] == id) {
			cola[i] = cola[i+1];
			id = cola[i+1];
		}
	}
	total--;
}

int primero_cola_listos() {
	return indice = ++indice % total;
}
