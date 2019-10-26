void inicializa_tarea(int id);

/*//////////////// INICIALIZA_TAREA() ////////////////////////////*/
void inicializa_tarea(int id) 
{
r = (struct RI *)PCB[id].stck + 1024 - sizeof(struct RI);

PCB[id].sp = FP_OFF((struct RI far *)r);
PCB[id].ss = FP_SEG((struct RI far *)r);
r->cs = FP_SEG(tarea);
r->ip = FP_OFF(tarea);
r->ds = _DS;
r->es = _ES;
r->flags = 0x20;

PCB[id].status = 1;
PCB[id].Dirseg = FP_SEG(tarea);
PCB[id].Diroff = FP_OFF(tarea);

Insertcola(id);
}
