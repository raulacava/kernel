#include <DOS.H>
#include "INIT.H"
#include "PROC0.H"
#include "MAN_CPU.H" // Context_Switch();

void init_pcb(void (*process)(), int id) {
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
}

////////////////////////////////////////////////////////////////////////////////
void init_system() {
	disable();
	old_clock = getvect(CLK_INT);
	setvect(CLK_INT, context_switch);
	activa(&proc0, 0);
}

void term_system() {
	setvect(CLK_INT, old_clock);
}

////////////////////////////////////////////////////////////////////////////////
void activa(void (*process)(), int id) {
	disable();
	init_pcb(process, id);
	meter_cola_listos(id);
	context_switch();
	enable();
}

void elimina(int id) {
	disable();
	sacar_cola_listos(id);
	context_switch();
	enable();
}
