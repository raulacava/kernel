#include<conio.h>
#include<DOS.H>
#include"MAIN.H"

#define ESC 27

void proceso2() {
	//La funcion de este proceso lo que hace es por medio una una operacion genera
	//numeros aleatorios los cuales las guarda en una variable, como se puede observar
	//se generan tres numeros aleatorios cada 3 segundos.
	struct text_info initial_info;
	//int msg_g_iActualProcess = 0, prev_secs = 999;
	int i;
	int posicionx, posiciony, inicialxo, inicialyo;
//	char salida;

	//Declaracion de la posicion en el cuadrante cuatro
	int cuadrante = 4; //cuadrante cuatro
	gettextinfo(&initial_info);
	inicialxo = (cuadrante == 1 || cuadrante == 3) ? 0 : initial_info.screenwidth /2;
	inicialyo = (cuadrante == 1 || cuadrante == 2) ? 0 : initial_info.screenheight/2;
	posicionx = 1;
	posiciony = 1;

//	for(i = 0; i<10; i++) {  
//		A[i]=(rand()%100);
//		printf("%d ",B[i]); 
//	}

	i = 1;
	while(i<=10) {
		//wait(id);
		B[i-1]=var_comun[i-1];
		disable(); gotoxy(posicionx + inicialxo + i*3, posiciony + inicialyo+1);
		disable(); printf("%d ", B[i-1]);
		enable(); delay(2000);
		
		//signal(id);
		i++;
	}
	printf("salio\n");
	while (1);
}//fin de proceso numeros aleatorios
// Lector
