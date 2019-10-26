#include "FUNC.h"
#include "DATOS.h"
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<graphics.h>


void t2(void)
{
int retraso=70000;

while(1)
{

for(y=14;y>1;y--)
{
disable();
gotoxy(20,y);
printf("o");
enable();

retraso=70000/y;
while(retraso)
{
retraso--;
}
disable();
gotoxy(20,y);
printf(" ");
enable();
}


for(y=2;y<15;y++)
{
disable();
gotoxy(20,y);
printf("o");
enable();

retraso=50000/y;
while(retraso)
{
retraso--;
}

disable();
gotoxy(20,y);
printf(" ");
enable();
}

};

}
