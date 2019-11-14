#define BUZZON_LENGTH  10
#define MSJ_LENGTH  20

typedef struct _mail {
   int encabezado;
   char msj[MSJ_LENGTH];
} buzz;

extern buzz buzzon[BUZZON_LENGTH];

extern int buzon_lleno; //bandera de buffer lleno
extern int buzon_vacio; //bandera de buffer vacio
extern int primer_msj;
extern int ultimo_msj;
extern int num_mensajes;

void recibe(char *);
void envia(char *);
