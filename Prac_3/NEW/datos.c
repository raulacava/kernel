#include <stdio.h>
#include "colas.h"

void lista_ciclada() {
	int i;
	for (i = 0; i < 20; i++) {
		printf("%d ", primero_cola_listos()+1);
	}
}

void mostrar() {
	int i;
	printf("%d - ", total);
	for (i = 0; i < 10; i++) {
		printf("%d ", cola[i]);
	}
	if (total != 0) {
		printf("- ");
		lista_ciclada();
	}
	printf("\n");
}
