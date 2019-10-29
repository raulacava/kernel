

void wait(int);
void signal(int);
void init_semaforo(int,int);

////////////////////////////////////////////////////////////////////////////////
extern int colaSem[10];
extern int totalSem;
extern int indiceSem;
extern int f2;

void init_cola_semaforo();
void meter_cola_semaforo(int);
void sacar_cola_semaforo(int);
