#include <stdio.h>
#include <dos.h>

typedef enum {READY, RUNNING} process_states;

typedef struct /*RI*/ {
	unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags;
} Regs_Int;

typedef struct /*procb*/ {
	unsigned id, DirSeg, DirOff, status, sp, ss, priority;
//	int      estado;
//	char     *nombre;
//	char far stck[1024];
	char stck[1024];
} PCB;

extern PCB DD[10];

PCB DD[10];

void init_pcb(void (*process)(), int id) {
	Regs_Int *r;

	r = (Regs_Int *) DD[id].stck + 1024 - sizeof(Regs_Int);
	DD[id].id = id;
	DD[id].priority = 0;
	DD[id].sp = FP_OFF((Regs_Int far *) r); // CHECK
	DD[id].ss = FP_SEG((Regs_Int far *) r); // CHECK
	DD[id].status = READY;                  // state
	DD[id].DirSeg = FP_SEG(process);        // next
	DD[id].DirOff = FP_OFF(process);        // prev

	r->cs = FP_SEG(process); // CHECK
	r->ip = FP_OFF(process); // CHECK
	r->ds = _DS;             // CHECK
	r->es = _ES;             // CHECK
	r->bp = _BP;
	r->di = _DI;
	r->si = _SI;
	r->dx = _DX;
	r->cx = _CX;
	r->bx = _BX;
	r->ax = _AX;
	r->flags = 0x20;         // CHECK
}

int main() {
	Regs_Int *r;
//	clrscr();
	printf("\nHello World! ========\n");

	printf("unsigned:   %5d bytes\n", sizeof(unsigned));
	printf("Regs_Int:   %5d bytes\n", sizeof(Regs_Int));
	printf("Regs_Int*:  %5d bytes\n", sizeof(Regs_Int*));
	printf("r:          %5d bytes\n", sizeof(r));
	printf("*r:         %5d bytes\n", sizeof(*r));
	printf("PCB:        %5d bytes\n", sizeof(PCB));
	printf("DD:         %5d bytes\n", sizeof(DD));
	printf("DD[0].stck: %5d bytes\n", sizeof(DD[0].stck + 1024));
	printf("DD[0].stck: %5d bytes\n", sizeof((Regs_Int *) DD[0].stck + 1024 - sizeof(Regs_Int)));
	printf("int:        %5d bytes\n", sizeof(int));
	printf("char*:      %5d bytes\n", sizeof(char*));

//	printf("\n_BP: %Fp", _BP);
//	printf("\n_SI: %Fp", _SI);
//	printf("\n_DI: %Fp", _DI);
//	printf("\n_DS: %Fp", _DS);
//	printf("\n_ES: %Fp", _ES);
//	printf("\n_DX: %Fp", _DX);
//	printf("\n_CX: %Fp", _CX);
//	printf("\n_BX: %Fp", _BX);
//	printf("\n_AX: %Fp", _AX);
//	printf("\n_IP: %Fp", _IP);
//	printf("\n_CS: %Fp", _CS);
//	printf("\nFLAG: %Fp", 0X20);
	printf("\n???: %Fp", (Regs_Int *) DD[0].stck + 1024 - sizeof(Regs_Int));

	printf("\n\n???: %Fp", DD[0].stck);
	printf(  "\n???: %Fp", DD[0].stck + 1024 - sizeof(Regs_Int));

	printf("\n\n???: %Fp", &DD[0].stck);
	printf(  "\n???: %Fp", &DD[0].stck + 1024 - sizeof(Regs_Int));

	printf("\n\n???: %Fp", (Regs_Int *)DD[0].stck);
	printf(  "\n???: %Fp", (Regs_Int *)DD[0].stck + 1024 - sizeof(Regs_Int));

	getch();
	return 0;
}
