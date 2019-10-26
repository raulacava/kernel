#include "FUNC.h"
#include "DATOS.h"
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<graphics.h>

void t4(void)
{
char buffer[20] = {0};
int posx = 5;
int posy = 245;

while(1)
{

if(kbhit())
{
char tecla = getch();

if(tecla==8)
{
sprintf(buffer, "Backspace");
disable();
outtextxy(posx, posy-10, buffer);
enable();
}
else if(tecla >='a' && tecla <= 'z')
{
posx = posx + 15;
sprintf(buffer, "%c",tecla);
disable();
outtextxy(posx, posy, buffer);
enable();
}


}

};

}


