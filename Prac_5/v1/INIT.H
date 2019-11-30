#define CLK_INT		0x08	/* vector de interrupcion del reloj */
#define STACK_SIZE	1024	/* capacidad maxima de la pila de los procesos */

typedef enum { READY, RUNNING } process_states;

typedef struct 
{
	unsigned bp, di, si, ds, es;
	unsigned dx, cx, bx, ax;
	unsigned ip, cs, flags;
}Regs_Int;

typedef struct 
{
	unsigned id;
	unsigned DirSeg;
	unsigned DirOff;
	unsigned status;
	unsigned sp;
	unsigned ss;
	unsigned priority;
	char     stack[STACK_SIZE];
}PCB;


extern PCB DD[10];
void init_pcb(void (*process)(void), int id);

extern void interrupt (*old_clock)();

void init_system();
void term_system();

void activa(void (*process)(), int id);
void elimina(int id);