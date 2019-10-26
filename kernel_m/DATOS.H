//Declaracion de variables globales
#include "MAIN.H"

Task Run;	//Variable tipo tarea para saber que tarea esta ejecutandose
Task *PtrRun = &Run;


int g_iTicks=0;
int g_iSeconds=0;
int g_bFirstRun=1;
int g_iActualProcess=0;
int g_iNumProcesses=0;
int g_iLastY=0;
int g_iLastX=0;
//indices de la cola de procesos
int g_head =0;
int g_tail = -1; 
int Cola_Procesos[10]; //Cola de 10 procesos
pcb pcbs[10];

var_comun[10]={0,0,0,0,0,0,0,0,0,0};
A[]={1,2,3,4,5,6,7,8,9,0};
B[10]={0,0,0,0,0,0,0,0,0,0};

void interrupt(*old_clock)();
