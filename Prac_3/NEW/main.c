#include <stdio.h>
#include "datos.h"
#include "colas.h"

int main() {
	int p = 4;
	printf("Hello World!\n");

	mostrar();
	for (int i = 1; i <= p; i++) {
		meter_cola_listos(i); mostrar();
	}
	for (int i = p; i >= 1; i--) {
		sacar_cola_listos(i); mostrar();
	}

	return 0;
}
