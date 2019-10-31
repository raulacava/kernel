extern int colaSem[10];
extern int totalSem;
extern int indiceSem;
extern int f2;
extern int sem;

void wait();
void signal();
void init_semaforo(int);

void init_cola_semaforo();
void sacar_cola_semaforo(int);
void meter_cola_semaforo(int);
