#include "FUNC.h"
#include "DATOS.h"
#include <dos.H>



void t3(void)
{
int retraso=6000;

while(1)
{
gettime(&t);

disable();
gotoxy(51,8);
printf("La hora es %d:%d:%d:%d",t.ti_hour,t.ti_min,t.ti_sec,t.ti_hund);
enable();

retraso = 6000;
while(retraso)
{
retraso--;
}

};

}

