#define STACK_SIZE 1024 // Capacidad Maxima de la Pila de Procesos
#define CLK_INT    0x08 // Vector de Interrupcion

typedef struct {
	unsigned bp, di, si, ds, es;
	unsigned dx, cx, bx, ax;
	unsigned ip, cs, flags;
} Regs_Int;

typedef enum {
	READY, 
	RUNNING
} process_states;

typedef struct {
	unsigned id;
	unsigned DirSeg;
	unsigned DirOff;
	unsigned status;
	unsigned sp;
	unsigned ss;
	unsigned priority;
	char     stack[STACK_SIZE];
//	process_states state;
} PCB;

typedef void (*TareaPtr)();

extern PCB DD[10];

void init_process(void (*process)(void), unsigned int id);

// Nuevo ///////////////////////////////////////////////////////////////////////
extern void interrupt (*old_clock)();
void init_system();
void term_system();
