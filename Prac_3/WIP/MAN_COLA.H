typedef struct {
	unsigned Este;
	void (*Tarea)();
} Task;

extern Task *PtrRun;
extern Task Run;              // Variable tipo Task, para saber que tarea esta ejecutandose
extern int g_head;
extern int g_tail;            // Indices de la cola de procesos
extern int Cola_Procesos[10]; // Cola de 10 procesos

void InsertaListos(Task *Tarea);
void add_to_queue(int id);
Task *PrimeraTarea();
