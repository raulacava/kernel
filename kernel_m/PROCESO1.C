#include <conio.h>
#include <DOS.h>

#define ESC 27

void proceso1() {
//La funcion de este proceso es obtener la hora de la computadora actualizando
//cada 60 segundos, posicionandolo en el cuadrante 2

	//Declaracion de variables
	struct text_info initial_info;
	struct time now;
	int posicionx, posiciony, inicialxo, inicialyo;
	char salida;
	int segundos = 60;
	
	//Declaracion de la posicion en el cuadrante dos
	int cuadrante = 2; //declaracion del cuadrante
	gettextinfo(&initial_info);
	inicialxo = (cuadrante == 1 || cuadrante == 3) ? 0 : initial_info.screenwidth /2;
	inicialyo = (cuadrante == 1 || cuadrante == 2) ? 0 : initial_info.screenheight/2;
	posicionx = initial_info.screenwidth /4;
	posiciony = initial_info.screenheight/4;

	//declaracion de las posiciones para el titulo "Timer"
	disable();
	gotoxy(inicialxo + posicionx - 5, inicialyo + posiciony - 1);
        disable();
	printf("TIMER");
	enable();

	//Empieza el ciclo
	while (salida != ESC) 
	{
	//if (kbhit()) salida = getch();
	//obtenemos el tiempo 
	gettime(&now);
	//se realiza una desicion para saber si los segundos 
	//son diferentes de los segundos obtenidos
	if (segundos != now.ti_sec) 
	  {
		disable();
		//posiciones para el printf de la hora
		gotoxy(inicialxo + posicionx - 4, inicialyo + posiciony);
		disable();
		//mostrar hora 
		printf("La hora es: %02d:%02d:%02d",now.ti_hour,now.ti_min,now.ti_sec);
		enable();
		segundos = now.ti_sec;
	  }//fin del if
	}//fin del while
}//fin proceso hora