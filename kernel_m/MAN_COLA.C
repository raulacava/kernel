#include "MAN_COLA.H"

void add_to_queue(int id) {
    g_tail++;
    Cola_Procesos[g_tail] = id;
}

Task *PrimeraTarea() {
    int aux, i;
    Task *T;
    aux = Cola_Procesos[g_head];
    T->Este = aux;
    g_tail--;

    for (i = g_head; i <= g_tail; i++) {
        Cola_Procesos[i] = Cola_Procesos[i + 1];
    }
    return T;
}

void InsertaListos(Task *Tarea) {
    add_to_queue(Tarea->Este);
}