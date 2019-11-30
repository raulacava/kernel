#include "MAN_BUZ.H"

/********************************************************
EN BUZON C
*********************************************************/
/*inicializacion de colas de buzon*/

queueS qfirst_buzzon = NULL;
queueS qlast_buzzon = NULL;
/**********************************************************
* Funciones de control de procesos bloqueados por buzon
***********************************************************/
int get_proceso_buzon_bloqueado (void){
   return buzzon_process_block;
}
void set_proceso_buzon_bloqueado (int status )
{
   if (status == 1 ){
      counter_process_block++;
   }else{
      counter_process_block--;
   }
   if (counter_process_block > 0){
      buzzon_process_block = 1;
   } 
   else{
      buzzon_process_block = 0;
   }
}

/******************************************************************************
*Funciones para copiar a buzzon el mensaje que (set_buzzon_mensaje) se envia o 
*para sacar el de buzon el mensaje que se recibe (get_buzzon_mensaje)
*************************************************************************/
void set_buzzon_mensaje (char* mensaje){
   num_mensajes++;
   memcpy(buzzon[ultimo_msj++].msj, (const char*)mensaje,MSJ_LENGTH);//meter mensaje a buzon
   if (ultimo_msj == BUZZON_LENGTH ) buzon_lleno= 1;
   if (primer_msj != ultimo_msj ) buzon_vacio = 0;
      ultimo_msj = ultimo_msj%MSJ_LENGTH;    
}

void get_buzzon_mensaje (char* mensaje){
   num_mensajes--;
   memcpy( mensaje, buzzon[primer_msj++].msj,MSJ_LENGTH);//meter mensaje a buzon y aumentamos contador
   if (primer_msj == ultimo_msj ) buzon_vacio = 1;
   primer_msj = primer_msj%MSJ_LENGTH;
}


/**********************************************************
* Funciones de enviar y recibir
***********************************************************/
void envia (char* Mensaje){
   int b;
   if (buzon_lleno == 1){ // buzzon lleno
      sacar_cola_listos(curr);
      push(&qfirst_buzzon, &qlast_buzzon , curr);//meter a cola de buzon
      set_proceso_buzon_bloqueado(1);
      context_switch();
   }

   set_buzzon_mensaje (Mensaje);
   
   if( get_proceso_buzon_bloqueado() == 1) {
      buzon_vacio = 0;
      b = pop(&qfirst_buzzon,&qlast_buzzon);// sacar de la cola de buzon
      set_proceso_buzon_bloqueado(0);//proceso desbloqueado
      meter_cola_listos(b);
	//	context_switch();
   }
}


void recibe (char * mensaje ){
   int b;
   if (buzon_vacio == 1){//if buzzon vacío
      sacar_cola_listos(curr);
      push(&qfirst_buzzon, &qlast_buzzon , curr);//meter a cola de buzon
      set_proceso_buzon_bloqueado(1);
      context_switch();
   }

   get_buzzon_mensaje (mensaje); //sacar mensaje de buzon
   
   
   /*esta lleno?*/
   if(get_proceso_buzon_bloqueado() == 1) {
      buzon_lleno = 0;
      b = pop(&qfirst_buzzon,&qlast_buzzon);// sacar de la cola de buzon
      set_proceso_buzon_bloqueado(0);//proceso desbloqueado
      meter_cola_listos(b);
	//	context_switch();
   }

}

