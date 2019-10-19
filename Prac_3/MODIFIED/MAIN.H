#ifndef DATOS_H
#define DATOS_H

#define ESC        27   // Tecla de salida
#define CLK_INT    0x08 // Vector de Interrupcion

/* variables globales */
extern int g_head;
extern int g_tail; // indices de la cola de procesos
extern int Cola_Procesos[10];      // Cola de 10 procesos

void add_to_queue(int id);
void proc1();
void proc2();
void proc3();
void proc4();

////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////

#endif
