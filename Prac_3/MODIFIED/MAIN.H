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


#endif
