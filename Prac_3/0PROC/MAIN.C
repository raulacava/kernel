#include <DATOS.H>

int main() {
	int bContinuerWhile = 1;
	g_head = 0;
	g_tail = -1;
	g_iActualProcess = g_iNumProcesses = g_iTicks = g_iSeconds = 0;
	g_bFirstRun = 1;
	g_iLastY = g_iLastX = 0;

	clrscr();

	init_process(&proc1, 1);
	init_process(&proc2, 2);
	init_process(&proc3, 3);
	init_process(&proc4, 4);

	g_iActualProcess = 0;

	old_clock = getvect(CLK_INT);

	setvect(CLK_INT, context_switch);

	while(bContinuerWhile);

	setvect(CLK_INT, old_clock);

	printf("press any key to continue\n");
	getch();
	return 0;
}

void add_to_queue(int id) {
	g_tail++;
	Cola_Procesos[g_tail] = id;
}

Task *PrimeraTarea() {
	int aux, i;
	Task *T;
	aux = Cola_Procesos[g_head];
	T->Este = aux;
	g_tail--;

	for (i = g_head; i <= g_tail; i++) {
		Cola_Procesos[i] = Cola_Procesos[i + 1];
	}

	return T;
}

void InsertaListos(Task *Tarea) {
	add_to_queue(Tarea->Este);
}

void interrupt context_switch() {
	disable();

	pcbs[PtrRun->Este].ss = _SS;
	pcbs[PtrRun->Este].sp = _SP;

	g_bFirstRun = 0;

	if (++g_iTicks >= 18) {
		g_iTicks = 0;
		g_iSeconds++;
	}

	InsertaListos(PtrRun);
	PtrRun = PrimeraTarea();

	_SS = pcbs[PtrRun->Este].ss;
	_SP = pcbs[PtrRun->Este].sp;
	gotoxy(g_iLastX,g_iLastY);
	old_clock();
	enable();
}

void init_process(TareaPtr Tarea, unsigned id) {
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

