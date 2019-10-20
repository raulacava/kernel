// Definiciones

Task Run;                   // Variable tipo tarea para saber que tarea esta ejecutandose
Task *PtrRun = &Run;
int g_iTicks = 0;
int g_iSeconds = 0;
int g_bFirstRun = 1;
int g_iLastY = 0;
int g_iLastX = 0;

int g_iActualProcess = 0;
int g_iNumProcesses = 0;

int g_head = 0;
int g_tail = -1;
int Cola_Procesos[10];      // Cola de 10 procesos

pcb pcbs[10];

void interrupt (*old_clock)();
