#include "MANCPU.h"
#include "DATOS.h"
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<graphics.h>

struct procb PCB[5] = {0};
f = 0;

void interrupt cambio_context(void)
{
disable();

if(f)
{
PCB[Primerocola()].ss = _SS;
PCB[Primerocola()].sp = _SP;

if(PCB[Primerocola()].status!=0)
Insertcola(Primerocola());

Eliminarcola();
}
else
f = 1;

_SS = PCB[Primerocola()].ss;
_SP = PCB[Primerocola()].sp;

prev();

enable();

if(kbhit() && getch() == 0xD)
{
setvect(8,prev);
closegraph();
exit(0);
}

}
