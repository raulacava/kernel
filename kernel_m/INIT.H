#define CLK_INT		0x08	/* vector de interrupcion del reloj */
#define STACK_SIZE	1024	/* capacidad maxima de la pila de los procesos */

typedef enum { READY, RUNNING } process_states;

typedef struct 
{
	unsigned bp, di, si, ds, es;
	unsigned dx, cx, bx, ax;
	unsigned ip, cs, flags;
}context;

typedef struct 
{
	unsigned int id;
	process_states state;
	unsigned ss;
	unsigned sp;
	char stack[STACK_SIZE];
	unsigned next;
	unsigned prev;
}pcb;

typedef void (*TareaPtr)();
extern pcb pcbs[10];
extern int g_iActualProcess;
extern int g_iNumProcesses;

void init_process(TareaPtr Tarea, unsigned id);

extern void interrupt (*old_clock)();

void init_system();
void term_system();