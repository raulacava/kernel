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
int candado=0; //recurso de cursor de pantalla libre

#define READY 1 // Constante para definir que un proceso esta listo
#define WAIT 2 // Constante para definir que un proceso esta esperando que un recurso se libere
#define EJEX 39
#define EJEY 11


void interrupt (*old_rutina) (void);
void interrupt context_switch(void);
void inicializa_tarea(TareaPtr Tarea, unsigned id);
void InsertaListos(Task *Tarea);
Task *PrimeraTarea();
void lock();
void unlock();
void mostrar();


//Funciones normales
void pelota(void);
void editor(void);
void reloj(void);
void letreros(void);
void dibuja_bordes();
void dibuja_cuadros(int offset);

//Funciones para cola
void inicializa_cola(int id);

int head=0, tail=-1; //indices de la cola de procesos
int timer1=0,timer2=0,timer3=0;

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
  T1->Tarea=pelota;
  T2->Este=2;
  T2->Tarea=editor;
  T3->Este=3;
  T3->Tarea=reloj;
  T4->Este=4;
  T4->Tarea=letreros;
  
  
  dibuja_bordes();
  old_rutina = getvect(8);
  setvect(8,context_switch);
  inicializa_tarea(T4->Tarea,T4->Este); 
  inicializa_tarea(T3->Tarea,T3->Este);
  inicializa_tarea(T1->Tarea,T1->Este);
  inicializa_tarea(T2->Tarea,T2->Este);
   
 
 
  
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
    
    //timer 
    timer1--;
    if(timer1<0)
        timer1=0;
        
     //timer 
    timer2--;
    if(timer2<0)
        timer2=0;
        
     //timer 
    timer3--;
    if(timer3<0)
        timer3=0;


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
		   InsertaListos(PtrRun);
		
		   PtrRun=PrimeraTarea();
		   _SS=DD[PtrRun->Este].ss;
		   _SP=DD[PtrRun->Este].sp;	
   	}



	}

//gotoxy(1,1);
//mostrar();

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

void lock()
{
	 while(candado!=0)
	    {
	    	//gotoxy(2,11);
	    	//printf("esperando...");//esperar hasta que el recurso este libre
	     }
	disable();
	 candado++;//obtener recurso
    enable();		   

   
}


void unlock()
{
	
	candado--;//liberar recurso
	
}

//CODIGO DE PROCESOS
void editor(void)
{
int x=2,y=17;
char ch; 

gotoxy(8,15);
printf("------EDITOR DE TEXTO-----");

  while(1){ 
  	if(y>=23)//en caso de que se hayan superado las lineas maximas
	{
		y=17;
	}
  	
	ch=getch();
	
	lock();
	gotoxy(x,y);//nos posicionamos en las coordenas x,y
	printf("%c",ch); //imprimir caracter
	unlock();
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
		
		lock();   
		gotoxy(x,y);//regresar una coordena a la izquierda
		printf(" ");//borrar letra anterior
		unlock();
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
  
  lock();
  gotoxy (xold,yold);
  printf(" ");
  unlock();

   
   lock();
    gotoxy (x,y); 
	printf("%c",o);
   unlock();
	xold=x;
	yold=y;
	//delay(100);
	
	timer2=1;
	while(timer2!=0)
	{
		
	}
	
 }
}


void reloj(void)
{
	int x,y,w;	
time_t tiempo = time(0);
struct tm *tlocal = localtime(&tiempo);

gotoxy(48,4);
printf("*******RELOJ DIGITAL********");


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
lock();
	            gotoxy(56,7);
				printf("%2.d%s%.2d%s%.2d",x,":",y,":",w);
	unlock();			
				timer3=18;
				while(timer3!=0)
				{
					//esperar hasta que pase 1 segundo
				}
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

/*	
	while(1)
	{
		/*
		switch(k)
		{
			case 0:  lock();
			          gotoxy(42,19);
					  printf("                    ");
					  unlock();
			         lock();
			         gotoxy(49,16);
			         printf("%s",l1);
					 unlock(); 
                    sleep(1);
                     
		      			
			break;
			case 1:
				    lock();
			         gotoxy(49,16);
			         printf("                    ");
					 unlock(); 
				    lock();
			        gotoxy(55,19);
					  printf("%s",l2);
					  unlock(); 
			         sleep(1);

 

			break;
			case 2: 
			          lock();
			          gotoxy(55,19);
					  printf("                    ");
					  unlock();
			         lock();
			         gotoxy(49,22);
			         printf("%s",l3);
					 unlock(); 
			         sleep(1);
	 

			break;
			case 3:  lock();
			          gotoxy(49,22);
					  printf("                    ");
					  unlock();
			         lock();
			         gotoxy(42,19);
			         printf("%s",l4);
			         unlock();
			         sleep(1);


		    break;
		}		
		k++;
		if(k==4)
		   k=0;//poner break
		   
		   lock();
		   gotoxy(42,19);
		   printf("%d",var);
		   unlock();
		   
           timer1=18;
           while(timer1!=0)
           {
           	
           }
           
		   var++;
		   if(var==10)
		       var=0;
		       
		      
	}*/
	
/*			char o=4;

int x=42, y=14,xold=42,yold=14;
int xnas=1, ynas=1;	
 while(1)
 {
  
  if (x<78 && xnas==1)
  x+=1;
  else
  xnas=0;
	if (x>43 && xnas==0)
  x-=1;
  else
  xnas=1;
  
   if (y<23 && ynas==1)
  y+=1;
  else
  ynas=0;
	if (y>14 && ynas==0)
  y-=1;
  else
  ynas=1;
  
  lock();
  gotoxy (xold,yold);
  printf(" ");
  unlock();

   
   lock();
    gotoxy (x,y); 
	printf("%c",o);
   unlock();
	xold=x;
	yold=y;
	//delay(100);
	
	timer1=1;
	while(timer1!=0)
	{
		
	}
	
 }*/
 
 while(1)
 {
 	       	if(var>3)
 	      		var=0;
 	      		
 	      	lock();
 	      	    gotoxy(42,19);
 	      	    printf("%s",l1[var]);
 	      	unlock();
 	      	var++;
            sleep(1);
            
 	  
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


