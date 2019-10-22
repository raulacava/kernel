// Definiciones

Task Run;                   // Variable tipo tarea para saber que tarea esta ejecutandose
Task *PtrRun = &Run;

int g_head = 0;
int g_tail = -1;
int Cola_Procesos[10];      // Cola de 10 procesos

PCB DD[10];

void interrupt (*old_clock)();
