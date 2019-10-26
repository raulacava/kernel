#include "FUNC.h"
#include "DATOS.h"
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<graphics.h>


void t5(void)
{
char c = 0;

while(1)
{

c = c%'Z';
if(c==0)
c = 'A';

disable();
gotoxy(62,23);
printf("%c",c++);
enable();

};

}

