#include<conio.h>
#include<DOS.H>
#include"MAIN.h"
#include "PROCESO0.H"
#include "PRINSEM.H"
#include "MAN_COLA.H"

#define ESC 27

void proceso3() {
	//La funcion de este proceso es al presionar una tecla, la plasma
	//en el cuadrante 3, realiza una decision si aun queda espacio 
	//vacio en el renglon sigue escribiendo, de lo contrario hara un 
	//salto de linea.

	//declaracion de variables 
	int posicionx,posiciony,i,j;
	char salida;
	int A[10];
	char msj[10][20] = {'m0','m1','m2','m3','m4','m5','m6','m7','m8','m9'}; 
	struct text_info initial_info;
	int inicialxo, inicialyo;
	int cuadrante = 3;

	//declaracion de cuadrante tres
	gettextinfo(&initial_info);
	inicialxo = (cuadrante == 1 || cuadrante == 3) ? 0 : initial_info.screenwidth /2;
	inicialyo = (cuadrante == 1 || cuadrante == 2) ? 0 : initial_info.screenheight/2;
	posicionx = 1;
	posiciony = 1;

	for(i = 0; i<10; i++) {
		wait();  
		A[i]=(rand()%100);
		disable();
		gotoxy(inicialxo + posicionx + i*3, posiciony + inicialyo);
		printf("%d ",A[i]);
		enable();
		var_comun[i]=A[i];
		delay(1000); 
		signal();	
		}
		
		elimina(curr);
}//fin proceso tres obtencion de tecla
// Escritor
