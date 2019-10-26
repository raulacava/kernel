#include "FUNC.h"
#include "DATOS.h"
#include "MANCOLAS.h"
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<graphics.h>


void t1(void)
{

rectangle(0, 0, 639, 479);
line(0, 239, 639, 239);
line(319, 0, 319, 479);


tarea = t2;
inicializa_tarea(2);

/*
tarea = t3;
inicializa_tarea(2);
*/
/*
tarea = t4;
inicializa_tarea(3);
*/
/*
tarea = t5;
inicializa_tarea(4);
*/

Terminarproces();
cambio_context();
}
