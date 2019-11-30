#include "queue.h"

int value=0; 


void wait (int id) //
{   
    //disable();
    queueS first = NULL, last = NULL;
    value = value - 1;
    if (value < 0) {

	// add process to queueS
	// here p is a process which is currently executing
	push(&first, &last, id);
	//sacar_cola_listos(id); // quita de cola de listos

    }
    else
	return;
       //	enable();
}

void signal (int id)
{  // disable();
    queueS first = NULL, last = NULL;
    int p;
    value = value + 1; 
    if (value <= 0) { 

	// remove process p from queueS
	p = pop(&first,&last);
      // meter_cola_listos(p);//wakeup(p); // mete a cola de listos
    }
    else
	return;
	//enable();
}