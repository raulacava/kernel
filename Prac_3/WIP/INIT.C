#include <DOS.H>
#include "INIT.H"
#include "MAN_CPU.H" // Context_Switch();

void init_process(void (*process)(void), unsigned id) {
	Regs_Int *r;
	r = (Regs_Int *) DD[id].stack + STACK_SIZE - sizeof(Regs_Int);

	DD[id].id = id;
	DD[id].priority = 0;
	DD[id].sp = FP_OFF((Regs_Int far *) r);
	DD[id].ss = FP_SEG((Regs_Int far *) r);
	DD[id].status = READY;
	DD[id].DirSeg = FP_SEG(process);
	DD[id].DirOff = FP_OFF(process);

	r->cs = FP_SEG(process);
	r->ip = FP_OFF(process);
	r->ds = _DS;
	r->es = _ES;
	r->bp = _BP;
	r->di = _DI;
	r->si = _SI;
	r->dx = _DX;
	r->cx = _CX;
	r->bx = _BX;
	r->ax = _AX;
	r->flags = 0x20;

	add_to_queue(id);
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
// typedef struct /*RI*/ {
// 	unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags;
// } Regs_Int;

// typedef struct /*procb*/ {
// 	unsigned id, DirSeg, DirOff, status, sp, ss, prioridad;
// 	int      estado;
// 	char     *nombre;
// 	char far stck[4096];
// } PCB;

// //extern Regs_Int DD;
// extern PCB PCBs[4];

// //Regs_Int DD;
// PCB DD[10];

// void init_pcb(void (*process)(), int id) {
// 	Regs_Int *r;

// 	r = (Regs_Int *) DD[id].stck + 1024 - sizeof( Regs_Int);
// 	DD[id].sp = FP_OFF((Regs_Int far *) r);
// 	DD[id].ss = FP_SEG((Regs_Int far *) r);
// 	r->cs = FP_SEG(process);
// 	r->ip = FP_OFF(process);
// 	r->ds = _DS;
// 	r->es = _DS;
// 	r->flags = 0x20;

// 	DD[id].estado = READY;
// 	DD[id].DirSeg = FP_SEG(process);
// 	DD[id].DirOff = FP_OFF(process);

// }

// void activa(void (*process)(), int id){
// 	init_pcb((*process)(), id);
// 	meter_colas_listos(id);
// 	cambio_contexto();
// }

// void elimina(id) {
// 	sacar_cola_listos(id);
// 	cambio_contexto();
// }
