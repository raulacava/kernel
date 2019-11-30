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

//BUZONH
buzz buzzon[BUZZON_LENGTH];
int buzon_lleno = 0; //bandera de buffer lleno
int buzon_vacio = 1; //bandera de buffer vacio
int buzzon_process_block = 0;
int counter_process_block = 0;
int primer_msj=0;
int ultimo_msj=0;
int num_mensajes=0;
