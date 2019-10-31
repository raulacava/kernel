#include <DOS.H>
#include <stdio.h>
#include <stdlib.h>
#include "MAN_COLA.H"
#include "MAN_CPU.H"
#include "PRISEM.H"
#include "queue.h"

queueS first = NULL;
queueS last = NULL;


void wait (void) {
	disable();
	sem--;
	if(sem < 0) {
		sacar_cola_listos(curr);
		printf("_push_cola_sem: %d\n", curr);
		push(&first, &last, curr);//meter a cola semaforos
	//	printf("_pop_cola_sem: %d\n",pop(&first,&last));
		context_switch();
	}
	enable();
}

void signal(void) {
	int p=255;
	disable();
	sem++;
	if(sem <= 0) {
		p = pop(&first,&last);// sacar de la cola de semaforos
		printf("_pop_cola_sem: %d\n", p);
		//meter_cola_listos(curr);
		context_switch();
	}
	enable();
}


////////////////////////////////////////////////////////////////////////////////
/*
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
*/
