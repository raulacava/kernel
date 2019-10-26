#include <DOS.H>
#include "INIT.H"
#include "MAN_CPU.H"

void init_process(TareaPtr Tarea, unsigned id)
{
	/* utiliza un apuntador para poder referenciar los registros en la pila por su nombre */

	context *cntxt_ptr;
	cntxt_ptr = (context *)pcbs[id].stack + STACK_SIZE - sizeof(context);

	/* inicializa el PCB del proceso */

	pcbs[id].id = id;
	pcbs[id].state = READY;
	pcbs[id].next = FP_SEG(Tarea);
    	pcbs[id].prev = FP_OFF(Tarea);
	pcbs[id].ss = FP_SEG((context far *) cntxt_ptr);
	pcbs[id].sp = FP_OFF((context far *) cntxt_ptr);

	/* inicializa los registros de la pila */

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

	/* incrementa el numero de procesos y el apuntador al siguiente proceso */
	add_to_queue(id);

	g_iNumProcesses++;
	g_iActualProcess++;

}

void init_system()
{
	old_clock=getvect(CLK_INT);
	setvect(CLK_INT, context_switch);
}

void term_system()
{
	setvect(CLK_INT,old_clock);
}