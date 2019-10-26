
struct time t;
extern char c;
extern int c5;
extern int y,retraso;

extern int count;

extern int f;

extern char buffer[20];
extern int posx ;
extern int posy;

extern const int tam = 7;
extern int cola[7];
extern int front,end;

struct procb
{
unsigned int id,
	 Dirseg,
	 Diroff,
	 status,
	 sp,
	 ss;
int estado;
unsigned prioridad;
char *nombre;
char stck[4096];
} extern PCB[5];

struct RI{
unsigned int bp,
	 di,
	 si,
	 ds,
	 es,
	 dx,
	 cx,
	 bx,
	 ax,
	 ip,
	 cs,
	 flags;
} extern *r;

void interrupt (*prev)(void);
void (*tarea)(void);

