#include <stdio.h>
#include "datos.h"
#include "colas.h"

int main() {
	int i;
	int p = 9;
	clrscr();
	printf("Hello World!\n");

	mostrar();
	for (i = 1; i <= p; i++) {
		meter_cola_listos(i); mostrar();
	}
	for (i = p; i >= 1; i--) {
		sacar_cola_listos(i); mostrar();
	}

	return 0;
}
