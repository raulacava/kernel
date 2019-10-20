#include <stdio.h>

int cola[10];
int total = 0;

void meter_cola_listos(int id) {
	cola[total] = id;
	total++;
}

void mostrar() {
	printf("%d - ", total);
	for (int i = 0; i < 10; i++) {
		printf("%d ", cola[i]);
	}
	printf("\n");
}