/*********************************************************
EN BUZON H
*********************************************************/
#include "MAN_COLA.H"
#include "queue.h"
#include <string.h>
#include <stdio.h>


//MAN_BUZZON;
#define BUZZON_LENGTH  10
#define MSJ_LENGTH  20
typedef struct _mail {
   int encabezado;
   char msj[MSJ_LENGTH];
}buzz;

extern buzz buzzon[BUZZON_LENGTH];

extern int buzon_lleno; //bandera de buffer lleno
extern int buzon_vacio; //bandera de buffer vacio
extern int primer_msj;
extern int ultimo_msj;
extern int num_mensajes;
extern int buzzon_process_block;
extern int counter_process_block;

int get_proceso_buzon_bloqueado (void);
void set_proceso_buzon_bloqueado (int);
void set_buzzon_mensaje (char*);
void get_buzzon_mensaje (char*);
void recibe (char*);
void envia (char*);
