#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>

typedef void (*TareaPtr)() ;

struct Ptask{
	unsigned Este;
    void (*Tarea)();
};

typedef struct Ptask Task;

#define READY 1; // Constante para definir que un proceso esta listo


void interrupt (*old_rutina) (void);
void interrupt context_switch(void);
void inicializa_tarea(TareaPtr Tarea, unsigned id);
void mostrar();
//InsertaListos(PtrRun,&Error);
//PrimeraTarea(&Error);

void InsertaListos(Task *Tarea);
Task *PrimeraTarea();

//Funciones para cola
void inicializa_cola(int id);

//Fin de funciones para la cola
void Proceso1();
void Proceso2();
void Proceso3();                                                                                                                 																																														
void Proceso4();

int head=0, tail=-1; //indices de la cola de procesos
int i=0;

/* Estructura de los regitros internos
en el orden que C++ los guarda en
una llamada a funcion tipo interrupcion*/
struct RI{
	unsigned bp;
	unsigned di;
	unsigned si;
	unsigned ds;
	unsigned es;
	unsigned dx;
	unsigned cx;
	unsigned bx;
	unsigned ax;
	unsigned ip;
	unsigned cs;
	unsigned flags;
};
typedef struct RI Regs_Int;


/* Estructura del PCB para cada tarea */
struct procb{
        unsigned id;                  //Identificador
        unsigned DirSeg;          //Semento de inicio de la tarea
        unsigned DirOff;          //Desplazamiento de inicio de la tarea
        unsigned status;           //Tiempo de espera en colo de retraso
        unsigned sp;                 //Apuntador de Pila local
        unsigned ss;                 //Apuntador de Pila Local
        int estado;          //Estado de la tarea
        unsigned prioridad;      //Prioridad de la tarea
        char *nombre;              //Nombre de la tarea
        char far stck[4096];      //Espacio de Pila Local
};

typedef struct procb PCB;       // para 20 procesos


Task *PtrRun=NULL;
int Cola_Procesos[10]; //Cola de 10 procesos
PCB DD[10];


int main( )
{
  Task *T1=(Task *)malloc(sizeof(Task));
  Task *T2=(Task *)malloc(sizeof(Task));
  Task *T3=(Task *)malloc(sizeof(Task));
  Task *T4=(Task *)malloc(sizeof(Task));
  
  T1->Este=1;
  T1->Tarea=Proceso1;
  T2->Este=2;
  T2->Tarea=Proceso2;
  T3->Este=3;
  T3->Tarea=Proceso3;
  T4->Este=4;
  T4->Tarea=Proceso4;
  
  old_rutina = getvect(8);
  setvect(8,context_switch);
  inicializa_tarea(T1->Tarea,T1->Este);
  inicializa_tarea(T2->Tarea,T2->Este);
  inicializa_tarea(T3->Tarea,T3->Este);
  inicializa_tarea(T4->Tarea,T4->Este);
  while(1);
}


void inicializa_tarea(TareaPtr Tarea, unsigned id){
Regs_Int *r;

      r = (Regs_Int *) DD[id].stck + 1024 - sizeof( Regs_Int);
      DD[id].sp = FP_OFF((Regs_Int far *) r);
      DD[id].ss = FP_SEG((Regs_Int far *) r);
      r->cs = FP_SEG(Tarea);
      r->ip = FP_OFF(Tarea);
      r->ds = _DS;
      r->es = _DS;
      r->flags = 0x20;

       DD[id].estado = READY;
      DD[id].DirSeg = FP_SEG(Tarea);
      DD[id].DirOff = FP_OFF(Tarea);

      inicializa_cola(id);
}


void interrupt context_switch(void){
disable();
i++;
if ( (i%20) ==0)
{   
   if(tail!=-1)//si la cola de Procesos no esta vacia
   {
   	if(PtrRun==NULL)
   	{
   		    PtrRun=PrimeraTarea();
		   _SS=DD[PtrRun->Este].ss;
		   _SP=DD[PtrRun->Este].sp;	
   	}
   	else
   	{
		   DD[PtrRun->Este].ss=_SS;
		   DD[PtrRun->Este].sp=_SP;
		   //InsertaListos(PtrRun,&Error);
		   InsertaListos(PtrRun);
		
		   //PtrRun=PrimeraTarea(&Error);
		   PtrRun=PrimeraTarea();
		   _SS=DD[PtrRun->Este].ss;
		   _SP=DD[PtrRun->Este].sp;	
   	}


   }
   
   i=0;
}
old_rutina();
enable();

}




void inicializa_cola(int id)
{
      tail++;
	  Cola_Procesos[tail]=id; 
}

void InsertaListos(Task *Tarea)
{	
    inicializa_cola(Tarea->Este);   
}

Task *PrimeraTarea()
{
	int aux;
	Task *T;
	aux=Cola_Procesos[head];
    T->Este=aux;
    tail--;
    
    for(i=head;i<=tail;i++){
    	Cola_Procesos[i]=Cola_Procesos[i+1];	
    }
       
        
    return T;
}

void mostrar()
{
    
   int h=0;
   
   for(h=head;h<=tail;h++)
      printf("%d \n",Cola_Procesos[h]);    

}

void Proceso1()
{
	while(1)
	{
		printf("Estoy en Proceso 1\n");
				
	}
}

void Proceso2()
{
	while(1)
	{
		printf("Estoy en Proceso 2\n");
		
		
	}
}

void Proceso3()
{
	while(1)
	{
		printf("Estoy en Proceso 3\n");
		
		
	}
}

void Proceso4()
{
	while(1)
	{
		printf("Estoy en Proceso 4\n");
			
	}
}
