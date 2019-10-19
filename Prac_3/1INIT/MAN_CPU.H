struct Ptask {
    unsigned Este;
    void (*Tarea)();
};

typedef struct Ptask Task;

extern Task *PtrRun;
extern Task Run;                   // Variable tipo tarea para saber que tarea esta ejecutandose
extern int g_iTicks;
extern int g_iSeconds;
extern int g_bFirstRun;
extern int g_iLastX;
extern int g_iLastY;

Task *PrimeraTarea();
void InsertaListos(Task *Tarea);
void interrupt context_switch();
