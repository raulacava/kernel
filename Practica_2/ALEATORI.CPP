#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <dos.h>
#include <iostream.h>

int main()
{
	srand(time(NULL));
	int x,y,z;
	while(!kbhit()){
	//genera un numero aleatorio
	x=(int)((rand()/32767.1)*100);
	printf("numero: %d\n",x);
	y=20+(int)((rand()/3276.1)*11);
	printf("numero: %d\n",y);
	z=30+(int)((rand()/3276.1)*22);
	printf("numero: %d\n",z);
	getch();
	clrscr();
	}
	return 0;
}