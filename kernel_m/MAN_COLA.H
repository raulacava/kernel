struct Ptask {
    unsigned Este;
    void (*Tarea)();
};

typedef struct Ptask Task;

extern Task *PtrRun;
extern Task Run;
extern int g_head;
extern int g_tail;
extern int Cola_Procesos[10];

void InsertaListos(Task *Tarea);
void add_to_queue(int id);
Task *PrimeraTarea();