#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include <time.h>

void dibuja_bordes();
void dibuja_cuadros(int offset);



void main ()
{
int a,b,c,d,x,y,w;	
time_t tiempo = time(0);
struct tm *tlocal = localtime(&tiempo);

dibuja_bordes();

x=tlocal->tm_hour;
//printf("Horas:");
//scanf("%d",&x);

y=tlocal->tm_min;
//printf("Minutos:");
//scanf("%d",&y) ;

w=tlocal->tm_sec;
//printf("Segundos:");
//scanf("%d",&w);

gotoxy(48,4);
printf("*******RELOJ DIGITAL********");
while(1)
{
	tiempo = time(0);
	tlocal = localtime(&tiempo);
	x=tlocal->tm_hour;

y=tlocal->tm_min;

w=tlocal->tm_sec;
	            gotoxy(56,7);
				printf("%2.d%s%.2d%s%.2d",x,":",y,":",w);
}


/*for(d=1;d<=365;d++)
{
	for(a=x;a<=23;a++)
	{
		if(a==23)x=0;
		c=0;
		b=0;

		for(b=y;b<=59;b++)
		{
			if(b==59)y=0;
			c=0;
			for(c=w;c<=59;c++)
			{
				if(c==59)w=0;
				gotoxy(56,7);
				printf("%2.d%s%.2d%s%.2d",a,":",b,":",c);
				sleep(1);
			}
		}
	}
}*/

}

void dibuja_bordes()
{

	clrscr();
	dibuja_cuadros(2);
	dibuja_cuadros(14);

}

void dibuja_cuadros(int offset)
{
	int i,j;
	for( i=1; i<=12;i++)
	{
		if(i==1)
		{
			gotoxy(1,i+offset);
			for(j=0;j<80;j++)
			{
				if(j==0)
				   printf("%c",201);
				else if(j>0 && j <39)
						printf("%c",205);
				else if(j==39)
				        printf("%c",187);
				else if(j==40)
						printf("%c",201);
			    else if(j>40 && j<79)
			           printf("%c",205);
			    else
							printf("%c",187);								   
			}
		}
		
		if(i>1 && i<12)
		{
			gotoxy(1,i+offset);
			printf("%c",186);
			gotoxy(40,i+offset);
			printf("%c",186);
			gotoxy(41,i+offset);
			printf("%c",186);
			gotoxy(80,i+offset);
			printf("%c",186);
		}
		
		if(i==12)
		{
			gotoxy(1,i+offset);
            for(j=0;j<80;j++)
			{
				if(j==0)
				   printf("%c",200);
				else if(j>0 && j <39)
						printf("%c",205);
				else if(j==39)
				        printf("%c",188);
				else if(j==40)
						printf("%c",200);
			    else if(j>40 && j<79)
			           printf("%c",205);
			    else
							printf("%c",188);								   
			}
		}	
	}
}
