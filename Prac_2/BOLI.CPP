//PROCESO 2: PELOTA QUE REBOTA
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <iostream.h>

void Inicializa();
void bolita(int ,int );

void main()
{
	Inicializa();
	bolita(100,100);
	getch();
	closegraph();
}

void bolita(int x,int y)
{
	//
	int r=15,Dx=1,Dy=1;
	int XMin=100,YMin=100,XMax=450,YMax=400;//puedes cambiar las dimensiones del rectangulo
	setcolor(WHITE);//color del rectangulo
	rectangle(XMin-(r+1),YMin-(r+1),XMax+(r+1),YMax+(r+1));

	//La funcion kbhit se utiliza para determinar si una tecla
	//ha sido presionada o no.
	while(!kbhit())
	{
		setcolor(CYAN);//color bolita
		circle(x,y,r);
		delay(1);//aqui cambia el tiempo
		setcolor(0);//traslado color
		circle(x,y,r);

		x+=Dx;
		y+=Dy;
		if ((x==XMin)||(x==XMax))//coordenadas en x
			Dx*=-1;
		if ((y==YMin)||(y==YMax))//coordenadas en y
			Dy*=-1;
	}
}
void Inicializa()
{
	//funcion initgraph inicializa el sistema de graficos al cargar un
	//controlador de graficos desde el disco
	int D=DETECT,M;
	initgraph(&D,&M,"C:\\TURBOC3\\BGI");
}