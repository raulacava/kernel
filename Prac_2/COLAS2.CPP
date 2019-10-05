#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <stdlib.h>

#define ESC 27

#define CLK_INT		0x08	/* vector de interrupcion del reloj */

#define STACK_SIZE	1024	/* capacidad maxima de la pila de los procesos */

#define LEFT_X		1
#define MIDDLE_X	40
#define RIGHT_X		80

#define TOP_Y		1
#define BOTTOM_Y	30
#define MIDDLE_Y	(BOTTOM_Y+1)/2

#define ENTER '\r'
#define BACKSPACE '\b'

typedef enum { READY, RUNNING } process_states;

typedef struct 
{
	unsigned bp, di, si, ds, es;
	unsigned dx, cx, bx, ax;
	unsigned ip, cs, flags;
} context;

typedef struct pcb 
{
	unsigned int id;
	process_states state;
	unsigned ss;
	unsigned sp;
	char stack[STACK_SIZE];
	unsigned next;
	unsigned prev;
} pcb;

struct Ptask {
    unsigned Este;
    void (*Tarea)();
};
typedef struct Ptask Task;
typedef void (*TareaPtr)();
/* variables globales */

pcb pcbs[10];
int g_iActualProcess, g_iNumProcesses, g_iTicks, g_iSeconds, g_bFirstRun;
int g_head =0, g_tail = -1; //indices de la cola de procesos
Task Run;//Variable tipo tarea para saber que tarea esta ejecutandose
Task *PtrRun = &Run;
int Cola_Procesos[10]; //Cola de 10 procesos
int g_iLastX, g_iLastY;

void interrupt (*old_clock)(...);

void interrupt context_switch(...);
// void fnInitFrame();
// void fnUninitializeFrame( );

// void process1();
// void process2();
// void process3();
// void process4();

void proc1();
void proc2();
void proc3();
void proc4();

void init_process(void (*process)(void), unsigned int id);

void add_to_queue(int id);
Task *PrimeraTarea();
void InsertaListos(Task *Tarea);
void mostrar();

int main()
{
	g_iLastY = g_iLastX = 0;
	/* limpia la pantalla */
	int bContinuerWhile = 1;
	clrscr();

	/* inicializa variables globales */

	g_iActualProcess = g_iNumProcesses = g_iTicks = g_iSeconds = 0;
	g_bFirstRun = 1;

	/* divide la pantalla en 4 cuadrantes */
	// fnInitFrame( );

	/* inicializa procesos */

	// init_process(&process1, 1);
	// init_process(&process2, 2);
	// init_process(&process3, 3);
	// init_process(&process4, 4);

	init_process(&proc1, 1);
	init_process(&proc2, 2);
	init_process(&proc3, 3);
	init_process(&proc4, 4);

	g_iActualProcess = 0;

	/* almacena la antigua rutina de interrupcion */

	old_clock = getvect(CLK_INT);

	/* instala la nueva rutina de interrupcion */

	setvect(CLK_INT, context_switch);

	/* comienza ejecucion del 1er proceso en la fila */

	while(bContinuerWhile);

	/* restaura la antigua rutina de interrupcion */

	setvect(CLK_INT, old_clock);

	/* espera a que el usuario presione una tecla para salir */

	printf("press any key to continue\n");
	getch();
	// fnUninitializeFrame( );
	return 0;
}

/* rutina de servicio de interrupcion para el reloj */
void interrupt context_switch(...)
{
	disable();

	// if (!g_bFirstRun) {

		/* salva la pila del proceso en ejecucion */

		pcbs[PtrRun->Este].ss = _SS;
		pcbs[PtrRun->Este].sp = _SP;
	// }

	g_bFirstRun = 0;

	/* incrementa la variable 'g_iSeconds' cada 18 interrupciones (cada segundo) */

	if (++g_iTicks >= 18) {

		g_iTicks = 0;
		g_iSeconds++;
	}

    InsertaListos(PtrRun);

    PtrRun = PrimeraTarea();

	/* apunta al siguiente proceso en la fila de procesos */

	// g_iActualProcess = (g_iActualProcess + 1) % g_iNumProcesses;

	/* cambia la pila por la del nuevo proceso en ejecucion */

	_SS = pcbs[PtrRun->Este].ss;
	_SP = pcbs[PtrRun->Este].sp;
	gotoxy(g_iLastX,g_iLastY);
	old_clock();
	enable();
}

/* rutina de servicio de interrupcion para el teclado */

// void fnInitFrame()
// {
// 	///*
// 	int gd = DETECT, gm;
// 	initgraph( &gd, &gm, "C:\\TURBOC3\\BGI");
// 	//get the width of the window.
// 	int iWinSizeX = getmaxx();
// 	//get the height of the window.
// 	int iWinSizeY = getmaxy();

// 	//Move the cursor to draw a horizontal line.
// 	moveto( 0,			iWinSizeY/2 );
// 	lineto( iWinSizeX,	iWinSizeY/2 );

// 	//Move the cursor to draw a vertical line.
// 	moveto( iWinSizeX/2,	0 );
// 	lineto( iWinSizeX/2,	iWinSizeY );
// 	//*/
// }

// void fnUninitializeFrame()
// {
// 	closegraph();
// }

// void process1()
// {
// 	time_t now;
// 	struct tm *tm_p;
// 	int prev_secs = 999;

// 	disable();
// 	gotoxy(45, 6);
// 	printf("this is your PC's clock");
// 	enable();

// 	while (1) {
// 		now = time(NULL);
// 		tm_p = localtime(&now);

// 		/* actualiza el reloj cada segundo */

// 		if (prev_secs != tm_p->tm_sec) {

// 			disable();
// 			gotoxy(45, 7);
// 			printf("the time is: %.2i:%.2i:%.2i", tm_p->tm_hour, tm_p->tm_min, tm_p->tm_sec);
// 			enable();

// 			prev_secs = tm_p->tm_sec;
// 		}
// 		delay(100);
// 	}
// }

// void process2()
// {
// 	int msg_g_iActualProcess = 0, prev_secs = 999;
// 	char *messages[] = { "have a nice day      ", "be happy             ", "don't forget to smile" };

// 	disable();
// 	gotoxy(45, 18);
// 	printf("here's a message for you");
// 	enable();

// 	int x, y;
 
// 	while (1) {

// 		/* cambia de mensaje cada 3 segundos */
// 		if (prev_secs != g_iSeconds && !(g_iSeconds % 3)) {

// 			disable();
// 			gotoxy(45, 19);
// 			printf("message: %s", messages[msg_g_iActualProcess]);
// 			enable();

// 			msg_g_iActualProcess = (msg_g_iActualProcess + 1) % 3;

// 			prev_secs = g_iSeconds;
// 		}
// 		sleep(1);
// 	}
// }

// void process3()
// {
// 	int c, curr_x, curr_y;
// 	curr_x = LEFT_X;
// 	curr_y = MIDDLE_Y + 1;
	
// 	while (1) 
// 	{
// 		g_iLastX = curr_x;
// 		g_iLastY = curr_y;
// 		gotoxy(curr_x, curr_y);
// 		c = getch();
// 		if( c != BACKSPACE && c != ENTER )
// 		{ 
// 			disable();
// 			curr_x++;
// 			printf("%c", c);
// 			enable();
// 		}
// 		/* si se alcanzo el final del cuadrante, retorna al inicio de la siguiente linea */
// 		if( c == BACKSPACE )
// 		{
// 			if( curr_x > LEFT_X )
// 			{
// 				disable();
// 				printf(" ");
// 				curr_x--;
// 				enable();
// 			}
// 			else if( curr_y > MIDDLE_Y + 1)
// 			{
// 				curr_x = MIDDLE_X;
// 				curr_y--;
// 			}
// 		}
// 		else if ( curr_x >= MIDDLE_X || c == ENTER ) 
// 		{
// 			curr_x = LEFT_X;
// 			curr_y++;
// 			if( curr_y > BOTTOM_Y )
// 				curr_y = MIDDLE_Y + 1;
// 		}
		
// 	}
// }

// void process4()
// {
// 	typedef enum { RIGHT, LEFT, DOWN, UP } direction;

// 	int prev_x, prev_y, curr_x, curr_y;
// 	direction dir_x, dir_y;

// 	prev_x = curr_x = prev_y = curr_y = 1;
// 	dir_x = RIGHT;
// 	dir_y = DOWN;

// 	while (1) 
// 	{
// 		/* borra la anterior posicion de la pelota */
// 		disable();
// 		gotoxy(prev_x, prev_y);
// 		printf(" ");
// 		enable();
// 		/* cambia la direccion en la que viaja la pelota (si toca algun borde) */

// 		if ((prev_x - 1) == 0) dir_x = RIGHT;
// 		if ((prev_x + 1) == MIDDLE_X) dir_x = LEFT;

// 		if ((prev_y - 1) == 0) dir_y = DOWN;
// 		if ((prev_y + 1) == MIDDLE_Y) dir_y = UP;

// 		/* actualiza la posicion de la pelota */

// 		if (dir_x == RIGHT) curr_x = prev_x + 1;
// 		else if (dir_x == LEFT) curr_x = prev_x - 1;

// 		if (dir_y == DOWN) curr_y = prev_y + 1;
// 		else if (dir_y == UP) curr_y = prev_y - 1;

// 		/* imprime la nueva posicion de la pelota */
// 		disable();
// 		gotoxy(curr_x, curr_y);
// 		printf("o");
// 		enable();
// 		prev_x = curr_x;
// 		prev_y = curr_y;

// 		delay(50);

//     }
// }

void init_process(TareaPtr Tarea, unsigned id)
{
	/* utiliza un apuntador para poder referenciar los registros en la pila por su nombre */

	context *cntxt_ptr;
	cntxt_ptr = (context *)pcbs[id].stack + STACK_SIZE - sizeof(context);

	/* inicializa el PCB del proceso */

	pcbs[id].id = id;
	pcbs[id].state = READY;
	pcbs[id].next = FP_SEG(Tarea);
    pcbs[id].prev = FP_OFF(Tarea);
	pcbs[id].ss = FP_SEG((context far *) cntxt_ptr);
	pcbs[id].sp = FP_OFF((context far *) cntxt_ptr);

	/* inicializa los registros de la pila */

	cntxt_ptr->bp = 0;
	cntxt_ptr->di = 0;
	cntxt_ptr->si = 0;
	cntxt_ptr->ds = _DS;
	cntxt_ptr->es = _ES;
	cntxt_ptr->dx = 0;
	cntxt_ptr->cx = 0;
	cntxt_ptr->bx = 0;
	cntxt_ptr->ax = 0;
	cntxt_ptr->cs = FP_SEG(Tarea);
	cntxt_ptr->ip = FP_OFF(Tarea);
	cntxt_ptr->flags = 0x200;

	/* incrementa el numero de procesos y el apuntador al siguiente proceso */

	add_to_queue(id);

	g_iNumProcesses++;
	g_iActualProcess++;
}

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

void mostrar()
{
    
   int h=0;
   
   for(h=g_head;h<=g_tail;h++){
      printf(" \n");    
   }

}

/******************************************************************************/

void proc1() {
	int n;
	char key;
	struct text_info initial_info;
	int xo, yo;
	int p = 1;

	gettextinfo(&initial_info);
	xo = p == 1 || p == 3 ? 0 : initial_info.screenwidth /2;
	yo = p == 1 || p == 2 ? 0 : initial_info.screenheight/2;

//	clrscr();
	gotoxy(xo + 1, n = yo + 1);
	while (key != ESC) {
		disable();
		key = getch();
		putch(key);
		enable();
		if (wherex() >= xo + initial_info.screenwidth/2)
			if (wherey() >= yo + initial_info.screenheight/2)
				gotoxy(xo + 1, n = yo + 1);
			else gotoxy(xo + 1, ++n);
	}
}

void proc2() {
	int x, y;
	int xs = 1, ys = 1;
	char key = 'o';
	struct text_info initial_info;
	int xo, yo;
	int p = 2;

	gettextinfo(&initial_info);
	xo = p == 1 || p == 3 ? 0 : initial_info.screenwidth /2;
	yo = p == 1 || p == 2 ? 0 : initial_info.screenheight/2;

	x = xo + 1;
	y = yo + 1;

//	clrscr();
	while (key != ESC) {
		if (kbhit()) key = getch();
		disable();
		gotoxy(x, y);
		putch('o');
		gotoxy(xo + 1, yo + 1);
		enable();
		delay(100);
		disable();
		gotoxy(x, y);
		putch(' ');
		enable();
		x += xs;
		y += ys;
		if (x >= xo + initial_info.screenwidth /2 || x <= xo + 1) xs = -xs;
		if (y >= yo + initial_info.screenheight/2 || y <= yo + 1) ys = -ys;
	}
}

void proc3() {
	struct text_info initial_info;
	int a, b, c;
	int x, y, xo, yo;
	char key;
	int p = 3;

	gettextinfo(&initial_info);
	xo = (p == 1 || p == 3) ? 0 : initial_info.screenwidth /2;
	yo = (p == 1 || p == 2) ? 0 : initial_info.screenheight/2;

	x = initial_info.screenwidth /4;
	y = initial_info.screenheight/4;

//	clrscr();
	while (key != ESC) {
		if (kbhit()) key = getch();
		//genera un numero aleatorio
		a = (int)((rand()/32767.1)*100);
		b = 20+(int)((rand()/3276.1)*11);
		c = 30+(int)((rand()/3276.1)*22);
		disable();
		gotoxy(xo + x - 5, yo + y - 1);
		printf("Numero: %3d", a);
		gotoxy(xo + x - 5, yo + y);
		printf("Numero: %3d", b);
		gotoxy(xo + x - 5, yo + y + 1);
		printf("Numero: %3d", c);
		enable();
		delay(100);
	}
}

void proc4() {
	struct text_info initial_info;
	struct time now;
	int x, y, xo, yo;
	char key;
	int s = 60;
	int p = 4;

	gettextinfo(&initial_info);
	xo = (p == 1 || p == 3) ? 0 : initial_info.screenwidth /2;
	yo = (p == 1 || p == 2) ? 0 : initial_info.screenheight/2;

	x = initial_info.screenwidth /4;
	y = initial_info.screenheight/4;

//	clrscr();
	while (key != ESC) {
		if (kbhit()) key = getch();
		gettime(&now);
		if (s != now.ti_sec) {
			disable();
			gotoxy(xo + x - 4, yo + y);
			printf("%02d:%02d:%02d", 
				now.ti_hour, 
				now.ti_min, 
				now.ti_sec);
			enable();
			s = now.ti_sec;
		}
	}
}
