#ifndef HEADER_H
#define HEADER_H

#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define ESC 27
#define CLK_INT		0x08	/* vector de interrupcion del reloj */
#define STACK_SIZE	1024	/* capacidad maxima de la pila de los procesos */

typedef enum { READY, RUNNING } process_states;

typedef struct 
{
	unsigned bp, di, si, ds, es;
	unsigned dx, cx, bx, ax;
	unsigned ip, cs, flags;
} context;

typedef struct pcb 
{
	unsigned int id;
	process_states state;
	unsigned ss;
	unsigned sp;
	char stack[STACK_SIZE];
	unsigned next;
	unsigned prev;
} pcb;

struct Ptask {
    unsigned Este;
    void (*Tarea)();
};
typedef struct Ptask Task;
typedef void (*TareaPtr)();

/* variables globales */

pcb pcbs[10];
int g_iActualProcess, g_iNumProcesses, g_iTicks, g_iSeconds, g_bFirstRun;
int g_head =0, g_tail = -1; //indices de la cola de procesos
Task Run;//Variable tipo tarea para saber que tarea esta ejecutandose
Task *PtrRun = &Run;
int Cola_Procesos[10]; //Cola de 10 procesos
int g_iLastX, g_iLastY;

void interrupt (*old_clock)();
void interrupt context_switch();
void proceso1();
void proceso2();
void proceso3();
void proceso4();
void init_process(void (*process)(void), unsigned int id);
void add_to_queue(int id);
Task *PrimeraTarea();
void InsertaListos(Task *Tarea);
void mostrar();

#endif