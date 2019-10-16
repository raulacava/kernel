#ifndef DATOS_H
#define DATOS_H

#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define ESC        27   // Tecla de salida
#define STACK_SIZE 1024 // Capacidad Maxima de la Pila de Procesos
#define CLK_INT    0x08 // Vector de Interrupcion

typedef enum {
	READY, 
	RUNNING
} process_states;

typedef struct {
	unsigned bp, di, si, ds, es;
	unsigned dx, cx, bx, ax;
	unsigned ip, cs, flags;
} context;

typedef struct pcb {
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
Task Run;                   // Variable tipo tarea para saber que tarea esta ejecutandose
Task *PtrRun = &Run;
int g_iActualProcess;
int g_iNumProcesses;
int g_iTicks;
int g_iSeconds;
int g_bFirstRun;
int g_head;
int g_tail; // indices de la cola de procesos
int Cola_Procesos[10];      // Cola de 10 procesos
int g_iLastX;
int g_iLastY;

void interrupt (*old_clock)();
void interrupt context_switch();
void proc1();
void proc2();
void proc3();
void proc4();
void init_process(void (*process)(void), unsigned int id);
void add_to_queue(int id);
Task *PrimeraTarea();
void InsertaListos(Task *Tarea);

#endif
