#include<conio.h>
#include<DOS.H>
#include "PROCESO0.H"

#define ESC 27
void proceso4() {
//La funcion de este proceso hace la traslacion de una pelota que este
//rebotando por todo el cuadrante numero 3, el cual refresca la posicion
//la pelota.

	//declaracion de variables 
	int posicionx,posiciony;
	int xs = 1, ys = 1;
	char salida = 'o';
	struct text_info initial_info;
	int inicialxo, inicialyo;
	int cuadrante = 1;

	//declaracion de cuadrantes
	gettextinfo(&initial_info);
	inicialxo = cuadrante == 1 || cuadrante == 3 ? 0 : initial_info.screenwidth /2;
	inicialyo = cuadrante == 1 || cuadrante == 2 ? 0 : initial_info.screenheight/2;
	posicionx = inicialxo + 1;
	posiciony = inicialyo + 1;

	//comienza el ciclo while 
	while (salida != ESC) {
		if (kbhit()) salida = getch();
		disable();
		gotoxy(posicionx, posiciony);
		putch('*');
		gotoxy(inicialxo + 1, inicialyo + 1);
		enable();
		delay(100);
		disable();
		gotoxy(posicionx, posiciony);
		putch(' ');
		enable();
		posicionx += xs;
		posiciony += ys;
		if (posicionx >= inicialxo + initial_info.screenwidth /2 || posicionx <= inicialxo + 1) xs = -xs;
		if (posiciony >= inicialyo + initial_info.screenheight/2 || posiciony <= inicialyo + 1) ys = -ys;
	}
}
