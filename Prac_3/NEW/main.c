#include <stdio.h>
#include "colas.h"

int main() {
	printf("Hello World!\n");

	mostrar();
	meter_cola_listos(1);
	mostrar();
	meter_cola_listos(2);
	mostrar();
	meter_cola_listos(3);
	mostrar();
	meter_cola_listos(4);
	mostrar();

	return 0;
}
