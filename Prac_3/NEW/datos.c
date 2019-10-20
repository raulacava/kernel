#include <stdio.h>
#include "colas.h"

void lista_ciclada() {
//	indice = -1;
	for (int i = 0; i < 27; i++) {
		printf("%d ", primero_cola_listos()+1);
	}
}

void mostrar() {
	printf("%d - ", total);
	for (int i = 0; i < 10; i++) {
		printf("%d ", cola[i]);
	}
	if (total != 0) {
		printf("- ");
		lista_ciclada();
	}
	printf("\n");
}
