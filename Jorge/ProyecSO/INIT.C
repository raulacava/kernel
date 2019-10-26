#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<graphics.h>
#include"datos.h"
#include"mancolas.h"
#include"mancpu.h"
#include"pripro.h"
#include"func.h"



/*/////////////////// MAIN() /////////////////////////*/
main() 
{
int gm, gd=DETECT;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

tarea = t1;
inicializa_tarea(0);
tarea = t6;
inicializa_tarea(1);

prev = getvect(8); 
setvect(8, cambio_context); 

while(!(kbhit() && getch() == 0x1B))
{
};

setvect(8,prev); 
closegraph();
exit(0);
}

