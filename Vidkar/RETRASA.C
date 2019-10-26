#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <time.h>

typedef void (*TareaPtr)() ;

struct Ptask{
	unsigned Este;
    void (*Tarea)();
};

typedef struct Ptask Task;


#define READY 1 // Constante para definir que un proceso esta listo
#define DELAYED 2 //Constante para definir que un proceso esta retrasado
#define RUNNING 3 //Constante para definir que un proceso esta en ejecución
#define EJEX 39
#define EJEY 11
#define MAX_DELAY 10 //cantidad maxima de procesos para manejar en cola de retrasados
#define MAX_PROC 10  //cantidad maxima de procesos para manejar en cola de procesos


void interrupt (*old_rutina) (void);
void interrupt context_switch(void);
void inicializa_tarea(TareaPtr Tarea, unsigned id);
void InsertaListos(Task *Tarea);
void Retrasa(unsigned id, unsigned tiempo);//funcion para agregar un proceso a la cola de retrasados
void Pop_retrasa(void);//funcion para quitar un proceso de la cola de retrasados
Task *PrimeraTarea();
void mostrar();



//Funciones normales
void pelota(void);
void editor(void);
void reloj(void);
void letreros(void);
void dibuja_bordes();
void dibuja_cuadros(int offset);

//Funciones para cola de procesos
void inicializa_cola(int id);
int head=0, tail=-1; //indices de la cola de procesos
int queueD_level=0; //variable auxiliar para verificar ocupación de la cola de retrasados
int ticks=0; //contador de ticks para funcion retrasa


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

typedef struct procb PCB[MAX_PROC];       // para 10 procesos

/* Estructura de un elemento de la cola de retrasados */
struct node_delayed{
    unsigned id;      //Identificador del proceso dormido
     unsigned tiempo; //tiempo de espera actual del proceso  
};

typedef struct node_delayed queue_d[MAX_DELAY];       // para 10 procesos

Task *PtrRun;
int Cola_Procesos[MAX_PROC]; //Cola de 10 procesos
queue_d QUEUE_DELAYED;
PCB DD;


int main( )
{

  dibuja_bordes();

  inicializa_tarea(&pelota,1); 
  inicializa_tarea(&editor,2);
  inicializa_tarea(&reloj,3);
  inicializa_tarea(&letreros,4);
  
  old_rutina = getvect(8);
  setvect(8,context_switch);
  
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
      if(PtrRun==NULL)
   		    PtrRun->Este=id;

}


void interrupt context_switch(void){
disable();
ticks++; //se aumenta el contador de ticks
       
       if(ticks==2) //se se contaron 2 ticks= 104 ms
       {
       	    ticks=0;
       	    if(queueD_level!=0)//si hay procesos retrasados
       	    {
       	        QUEUE_DELAYED[0].tiempo--;// se actualiza tiempo de espera de primer proceso
       	        Pop_retrasa(); //Sacar procesos que hayan cumplido su tiempo en la cola de espera y pasarlos a cola de listos 	
       	    }
       	    
       }
    
	   DD[PtrRun->Este].ss=_SS;
	   DD[PtrRun->Este].sp=_SP;
	   if(DD[PtrRun->Este].status==READY)
	   		InsertaListos(PtrRun);
			
	   PtrRun=PrimeraTarea();
	   _SS=DD[PtrRun->Este].ss;
	   _SP=DD[PtrRun->Este].sp;	

   

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
	int aux,i;
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

void Retrasa(unsigned id, unsigned tiempo)//funcion para agregar un proceso a la cola de retrasados
{
	int acum=0; //variable auxiliar para acumular tiempo de espera de procesos
	int i=0,j=0;
	int encontrado=0;
	disable();

	
	if(queueD_level<MAX_DELAY) //si hay especio disponible para meter un proceso a cola de retrasados
	{
		DD[id].status=DELAYED; //cambiar estado del proceso a delayed
		
		if(queueD_level==0) //si la cola esta vacia
		{
			//agregar datos del primer proceso que entrara a a cola
			QUEUE_DELAYED[0].id=id;
			QUEUE_DELAYED[0].tiempo=tiempo;			
		}
		else
		{
			encontrado=0;//bandera para saber si se encontro posicion para el proceso
			for(i=0;i<MAX_DELAY;i++) // ciclo for para recorrer la cola en busca de la posición adecuada para el proceso que se va a insertar
			{
				acum+=QUEUE_DELAYED[i].tiempo;//acumular el tiempo del proceso i de la cola
				
				if(tiempo <= acum) //si el tiempo del proceso que quiere entrar a la cola es menor o igual que el acumulado
				{
					 //recorrer elementos a la derecha a partir de donde se insertara el nuevo proceso
					 for(j=queueD_level;j>=i;j--)
					 {
					 	QUEUE_DELAYED[j+1].tiempo=QUEUE_DELAYED[j].tiempo;
					 	QUEUE_DELAYED[j+1].id=QUEUE_DELAYED[j].id;
					 }
					 
					 //insertar el proceso nuevo
					 QUEUE_DELAYED[i].tiempo=tiempo-acum;
					 QUEUE_DELAYED[i].id=id;
					 
					 //actualizar tiempo del proceso adyacente a la derecha
					 QUEUE_DELAYED[i+1].tiempo= QUEUE_DELAYED[i+1].tiempo- QUEUE_DELAYED[i].tiempo;
					 queueD_level++;
					 encontrado=1;
					 break;					 
				}
				
			}
			
			if(encontrado==0)//si no se encontro posicion para el proceso, significa que es mas grande que todos los tiempos
			{				// y debe ser insertado al final de la cola
				 //insertar el proceso nuevo
				 queueD_level++;
			     QUEUE_DELAYED[queueD_level].tiempo= tiempo-QUEUE_DELAYED[queueD_level-1].tiempo;
				 QUEUE_DELAYED[queueD_level].id=id;				 
			}
		}
		

		
	}
	
	enable();
	context_switch();
	
}


void Pop_retrasa(void)//funcion para quitar un proceso de la cola de retrasados
{
	//Esta funcion busca los procesos que tengan un tiempo cero de retraso para sacarlos de la cola
	int i=0;
	Task *Tarea;
	
	while(QUEUE_DELAYED[0].tiempo==0) // mientras el primer proceso de la cola tiene tiempo cero
	{
		DD[QUEUE_DELAYED[0].id].status=READY; //cambiar estado del proceso a READY
		Tarea->Este=QUEUE_DELAYED[0].id;
		InsertaListos(Tarea); //insertar en cola de listos el proceso que estaba dormido
		
		//Ahora se debe recorrer la cola
		for(i=0;i<queueD_level;i++)
		{
			QUEUE_DELAYED[i].tiempo=QUEUE_DELAYED[i+1].tiempo;
			QUEUE_DELAYED[i].id=QUEUE_DELAYED[i+1].id;	
		}
		
		queueD_level--;
	}
	
}



//CODIGO DE PROCESOS
void editor(void)
{
int x=2,y=17;
char ch; 

disable();
gotoxy(8,15);
printf("------EDITOR DE TEXTO-----");
enable();
  while(1){ 
  	if(y>=23)//en caso de que se hayan superado las lineas maximas
	{
		y=17;
	}
  	
	ch=getch();
	
    disable();
	gotoxy(x,y);//nos posicionamos en las coordenas x,y
	printf("%c",ch); //imprimir caracter
	enable();
	if (ch==13) //si el caracter fue "enter"
	{
		x=1;//reiniciar x
		y++;//aumentar linea
		
	} 
	
	
	if (ch==8)//si es tecla backspace
	{
		x=x-1;
		if(x==1)
		{
			x=37;
			y--;
			if(y<17)
			{
			   y=17;
			   x=2;	
			}
			   
		}
		
	    disable();
		gotoxy(x,y);//regresar una coordena a la izquierda
		printf(" ");//borrar letra anterior
		enable();
		x--;//reestablecer 
		
		if(x<=1 && y>17)
		{
			x=37;
			y--;
		}
		else if(x<=1 && y<=17)
		{
			x=1;
			y=17;
		}
		
	} 
	
	
	
	x++;
		if(x==39)
		{
			x=2;
			y++;
		} 
	} 
	
}


void pelota(void)
{
		char o=4;

int x=2, y=2,xold=2,yold=2;
int xnas=1, ynas=1;	
 while(1)
 {
  
  if (x<EJEX && xnas==1)
  x+=1;
  else
  xnas=0;
	if (x>2 && xnas==0)
  x-=1;
  else
  xnas=1;
  
   if (y<EJEY && ynas==1)
  y+=1;
  else
  ynas=0;
	if (y>2 && ynas==0)
  y-=1;
  else
  ynas=1;
  
disable();
  gotoxy (xold,yold);
  printf(" ");
 enable();

   
disable();
    gotoxy (x,y); 
	printf("%c",o);
  enable();
	xold=x;
	yold=y;

   //delay(50);
   Retrasa(PtrRun->Este, 10);//retrasar 400 ms
   
	
 }
}


void reloj(void)
{
	int x,y,w;	
time_t tiempo = time(0);
struct tm *tlocal = localtime(&tiempo);

disable();
gotoxy(48,4);
printf("*******RELOJ DIGITAL********");
enable();

x=tlocal->tm_hour;
y=tlocal->tm_min;
w=tlocal->tm_sec;

while(1)
{
	tiempo = time(0);
	tlocal = localtime(&tiempo);
	x=tlocal->tm_hour;

y=tlocal->tm_min;

w=tlocal->tm_sec;
disable();
	            gotoxy(56,7);
				printf("%2.d%s%.2d%s%.2d",x,":",y,":",w);
	enable();	        
		      delay(100);
		       //Retrasa(PtrRun->Este, 5);//retrasar 500 ms

}



}

void letreros(void)
{
	int var=0;
	double temp=0;
	char *l1[4];
	l1[0]="=====ANUNCIO 1====";
	l1[1]="=====ANUNCIO 2====";
	l1[2]="=====ANUNCIO 3====";
	l1[3]="=====ANUNCIO 4====";

 
 while(1)
 {
 	       	if(var>3)
 	      		var=0;
 	      		
 	      disable();
 	      	    gotoxy(42,19);
 	      	    printf("%s",l1[var]);
 	      enable();
 	      	var++;
 	      	        		
         sleep(1);
         //Retrasa(PtrRun->Este, 10);//retrasar 1 s
           
 	  
 }



}

//funciones para dibujar el marco de division
void dibuja_bordes()
{

	clrscr();
	dibuja_cuadros(2);
	dibuja_cuadros(14);

}

void dibuja_cuadros(int offset)
{
	int i,j;
	for( i=1; i<=12;i++)
	{
		if(i==1)
		{
			gotoxy(1,i+offset);
			for(j=0;j<80;j++)
			{
				if(j==0)
				   printf("%c",201);
				else if(j>0 && j <39)
						printf("%c",205);
				else if(j==39)
				        printf("%c",187);
				else if(j==40)
						printf("%c",201);
			    else if(j>40 && j<79)
			           printf("%c",205);
			    else
							printf("%c",187);								   
			}
		}
		
		if(i>1 && i<12)
		{
			gotoxy(1,i+offset);
			printf("%c",186);
			gotoxy(40,i+offset);
			printf("%c",186);
			gotoxy(41,i+offset);
			printf("%c",186);
			gotoxy(80,i+offset);
			printf("%c",186);
		}
		
		if(i==12)
		{
			gotoxy(1,i+offset);
            for(j=0;j<80;j++)
			{
				if(j==0)
				   printf("%c",200);
				else if(j>0 && j <39)
						printf("%c",205);
				else if(j==39)
				        printf("%c",188);
				else if(j==40)
						printf("%c",200);
			    else if(j>40 && j<79)
			           printf("%c",205);
			    else
							printf("%c",188);								   
			}
		}	
	}
} 


