#include<conio.h>
#include<DOS.H>
#include"MAIN.h"

#define ESC 27

void proceso3() {
	//La funcion de este proceso es al presionar una tecla, la plasma
	//en el cuadrante 3, realiza una decision si aun queda espacio 
	//vacio en el renglon sigue escribiendo, de lo contrario hara un 
	//salto de linea.

	//declaracion de variables 
	int posicionx,posiciony,i;
	char salida;
	struct text_info initial_info;
	int inicialxo, inicialyo;
	int cuadrante = 3;

	//declaracion de cuadrante tres
	gettextinfo(&initial_info);
	inicialxo = (cuadrante == 1 || cuadrante == 3) ? 0 : initial_info.screenwidth /2;
	inicialyo = (cuadrante == 1 || cuadrante == 2) ? 0 : initial_info.screenheight/2;
	posicionx = 1;
	posiciony = 1;

//	for(i = 0; i<10; i++) {  
//		A[i]=(rand()%100);
//		printf("%d ",A[i]); 
//	}

	i=1;
	while(i<=10) {
		//wait(id);
		var_comun[i-1]=A[i-1];
		disable(); gotoxy(inicialxo + posicionx + i*3, posiciony + inicialyo);
		disable(); printf("%d ", var_comun[i-1]);
		enable(); delay(2000);
		
		//signal(id);
		i++;
	}
	while (1);
}//fin proceso tres obtencion de tecla
// Escritor
