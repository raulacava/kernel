#include <string.h>
#include <stdio.h>
#include "MAN_BUZ.H"
#include "queue.h"
#include "MAN_COLA.H"

/*inicializacion de colas de buzon*/

queueS qfirst_buzzon = NULL;
queueS qlast_buzzon = NULL;

//void envia (int id_process, char* Mensaje){
void envia(char* Mensaje){
   int b;
   if (buzon_lleno == 1){
      push(&qfirst_buzzon, &qlast_buzzon , curr);//meter a cola de buzon
      context_switch();
   }else{
      num_mensajes++;
      memcpy(buzzon[ultimo_msj++].msj, (const char*)Mensaje,MSJ_LENGTH);//meter mensaje a buzon
      if (ultimo_msj == BUZZON_LENGTH ) buzon_lleno= 1;
      ultimo_msj = ultimo_msj%MSJ_LENGTH;  
   }
   if(buzon_vacio == 1) {
      buzon_vacio = 0;
      b = pop(&qfirst_buzzon,&qlast_buzzon);// sacar de la cola de buzon
      meter_cola_listos(b);
		context_switch();
   }
}


//void recibe (int id_process, char * mensaje ){
void recibe(char * mensaje){
   int b;
   if (buzon_vacio == 1){//if buzzon vacío
      push(&qfirst_buzzon, &qlast_buzzon , curr);//meter a cola de buzon
      context_switch();
   }else{
      num_mensajes--;
      memcpy( mensaje, buzzon[primer_msj++].msj,MSJ_LENGTH);//meter mensaje a buzon y aumentamos contador
      if (primer_msj == BUZZON_LENGTH || primer_msj == ultimo_msj ) buzon_vacio = 1;
      primer_msj = primer_msj%MSJ_LENGTH;
   }
   if(buzon_lleno == 1) {
      buzon_lleno = 0;
      b = pop(&qfirst_buzzon,&qlast_buzzon);// sacar de la cola de buzon
      meter_cola_listos(b);
		context_switch();
   }

}



/*
el turboC No acepta el #include "MAN_BUZON.H"
*/