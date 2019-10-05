#include <stdio.h>
#include <dos.h>

typedef struct /*RI*/ {
	unsigned bp;

	unsigned di;
	unsigned si;

	unsigned ds;

	unsigned es;
	unsigned dx;
	unsigned cx;
	unsigned bx;
	unsigned ax;

	unsigned ip;
	unsigned cs;

	unsigned flags;
} Regs_Int;
//typedef RI Regs_Int;

/* Estructura del PCB para cada tarea */
typedef struct /*procb*/ {
	unsigned id;         // Identificador
	unsigned DirSeg;     // Semento de inicio de la tarea
	unsigned DirOff;     // Desplazamiento de inicio de la tarea
	unsigned status;     // Tiempo de espera en colo de retraso

	unsigned sp;         // Apuntador de Pila local
	unsigned ss;         // Apuntador de Pila Local

	int      estado;     // Estado de la tarea
	unsigned prioridad;  // Prioridad de la tarea
	char     *nombre;    // Nombre de la tarea
	char far stck[4096]; // Espacio de Pila Local
} PCB;
//typedef procb PCB[20];   // para 20 procesos

Regs_Int DD;        // Registros Internos
PCB PCBs[4]; // PCBs de los Procesos

void interrupt context_switch(void) {
	disable();

	DD[PtrRun->Este].ss = _SS;
	DD[PtrRun->Este].sp = _SP;
	InsertaListos(PtrRun, &Error);

	PtrRun = PrimeraTarea(&Error);
	_SS = DD[PtrRun->Este].ss;
	_SP = DD[PtrRun->Este].sp;
	enable();
	old_Routine();
}


// typedef void (*TareaPtr)();
// void init_Process(TareaPtr process, unsigned id);
void init_Process(void (*process)(), unsigned id);

int main() {
	clrscr();
	DD.flags = 123;
	printf("%d", DD.flags);
	PCBs[0].id = 11;
	printf("%d", PCBs[0].id);

	// Inicializar los procesos.
	init_Process(proc1, 1);
	init_Process(proc2, 2);

	getch();

	return 0;
}

// void init_Process(TareaPtr process, unsigned id) {
void init_Process(void (*process)(), unsigned id) {
	Regs_Int *r;

	r = (Regs_Int *) DD[id].stck + 1024 - sizeof( Regs_Int);
	DD[id].sp = FP_OFF((Regs_Int far *) r);
	DD[id].ss = FP_SEG((Regs_Int far *) r);
	r->cs = FP_SEG(process);
	r->ip = FP_OFF(process);
	r->ds = _DS;
	r->es = _DS;
	r->flags = 0x20;

	DD[id].estado = READY;
	DD[id].DirSeg = FP_SEG(process);
	DD[id].DirOff = FP_OFF(process);

	inicializa_cola(id);
}

