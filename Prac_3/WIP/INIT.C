#include <DOS.H>
#include "INIT.H"
#include "MAN_CPU.H" // Context_Switch();

void init_process(TareaPtr Tarea, unsigned id) {
//void init_process(void (*process)(void), unsigned id) {
	context *cntxt_ptr;
	cntxt_ptr = (context *)pcbs[id].stack + STACK_SIZE - sizeof(context);

	pcbs[id].id = id;
	pcbs[id].state = READY;
	pcbs[id].next = FP_SEG(Tarea);
	pcbs[id].prev = FP_OFF(Tarea);
	pcbs[id].ss = FP_SEG((context far *) cntxt_ptr);
	pcbs[id].sp = FP_OFF((context far *) cntxt_ptr);

	cntxt_ptr->bp = 0;
	cntxt_ptr->di = 0;
	cntxt_ptr->si = 0;
	cntxt_ptr->ds = _DS;
	cntxt_ptr->es = _ES;
	cntxt_ptr->dx = 0;
	cntxt_ptr->cx = 0;
	cntxt_ptr->bx = 0;
	cntxt_ptr->ax = 0;
	cntxt_ptr->cs = FP_SEG(Tarea);
	cntxt_ptr->ip = FP_OFF(Tarea);
	cntxt_ptr->flags = 0x200;

	add_to_queue(id);

	g_iNumProcesses++;
	g_iActualProcess++;
}

////////////////////////////////////////////////////////////////////////////////
void init_system() {
	// activa(&proc0, 0);
	old_clock = getvect(CLK_INT);
	setvect(CLK_INT, context_switch);
}

void term_system() {
	setvect(CLK_INT, old_clock);
}

// Nuevo ///////////////////////////////////////////////////////////////////////
typedef struct /*RI*/ {
	unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags;
} Regs_Int;

typedef struct /*procb*/ {
	unsigned id, DirSeg, DirOff, status, sp, ss, prioridad;
	int      estado;
	char     *nombre;
	char far stck[4096];
} PCB;

//extern Regs_Int DD;
extern PCB PCBs[4];

//Regs_Int DD;
PCB DD[10];

void init_pcb(void (*process)(), int id) {
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

}

void activa(void (*process)(), int id){
	init_pcb((*process)(), id);
	meter_colas_listos(id);
	cambio_contexto();
}

void elimina(id) {
	sacar_cola_listos(id);
	cambio_contexto();
}
