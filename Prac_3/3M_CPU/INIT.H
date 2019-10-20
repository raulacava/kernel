#define STACK_SIZE 1024 // Capacidad Maxima de la Pila de Procesos
#define CLK_INT    0x08 // Vector de Interrupcion

typedef struct {
	unsigned bp, di, si, ds, es;
	unsigned dx, cx, bx, ax;
	unsigned ip, cs, flags;
} context;

typedef enum {
	READY, 
	RUNNING
} process_states;

typedef struct {
	unsigned int id;
	process_states state;
	unsigned ss;
	unsigned sp;
	char stack[STACK_SIZE];
	unsigned next;
	unsigned prev;
} pcb;

typedef void (*TareaPtr)();

extern pcb pcbs[10];
extern int g_iActualProcess;
extern int g_iNumProcesses;

//void init_process(void (*process)(void), unsigned int id);
void init_process(TareaPtr Tarea, unsigned id);

// Nuevo ///////////////////////////////////////////////////////////////////////
extern void interrupt (*old_clock)();
void init_system();
void term_system();
