#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

void dibuja_bordes();
void dibuja_cuadros(int offset);



#define EJEX 39
#define EJEY 11



int main(){
	
	char o=4;

int x=2, y=2,xold=2,yold=2;
int xnas=1, ynas=1;

	dibuja_bordes();
	
 do{
  
  if (x<EJEX && xnas==1)
  x+=1;
  else
  xnas=0;
	if (x>2 && xnas==0)
  x-=1;
  else
  xnas=1;
  
   if (y<EJEY && ynas==1)
  y+=1;
  else
  ynas=0;
	if (y>2 && ynas==0)
  y-=1;
  else
  ynas=1;
  
  //clrscr();
  gotoxy (xold,yold);
   printf(" ");
  gotoxy (x,y); 
	printf("%c",o);
	xold=x;
	yold=y;
	delay(100);
 }while(1);
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
