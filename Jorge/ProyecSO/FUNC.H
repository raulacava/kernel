
void t1(void);
void t2(void);
void t3(void);
void t5(void);
void t6(void);
void t4(void);
/* ***************************************** */

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
/* ***************************************** */

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
/* ***************************************** */

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
/* ***************************************** */

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
outtextxy(posx, posy-20, buffer);
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
/* ***************************************** */

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
/* ***************************************** */

void t6(void)
{

while(1)
{
disable();
enable();
};

}


