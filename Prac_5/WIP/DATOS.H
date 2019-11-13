// Definiciones

// MAIN.H
int isOn = 1;
int infty = 1;

// INIT.H
PCB DD[10];
void interrupt (*old_clock)();
int f = 0;

// MAN_COLA.H
int cola[10];
int total = 0;
int indice = -1;
int curr;
int next;
//int f = 0;

// PROC0.H
int var_global[10];

// PRISEM.H
int colaSem[10];
int totalSem = 0;
int indiceSem = -1;
int f2;
int sem = 1;

