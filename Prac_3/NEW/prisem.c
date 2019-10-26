void wait (int id)
{
	disable();
	s[id].valor--;
	if(s[id].valor<0){
		sacar_cola_listos(id);
		mete_cola_semaforo(id);
		cambio_contexto();
		enable();
	}
	
}

void signal(int id){
	disable();
	s[id].valor++;
	if(s[id].valor<=0){
		sacar_cola_semaforo(id);
		mete_cola_listo(id);
		cambio_contexto();
		enable();
	}
}

void init_semaforo(int id){
s[id].valor=1;
init_cola_semaforo();

}