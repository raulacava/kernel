#ifndef queue_h
#define queue_h
/**/
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
   int value;
   struct _node *next;
} node;

typedef node* queueS;


/* Funciones con colas: */
void push(queueS *first, queueS *last, int v);
int pop(queueS *first, queueS *last);
#endif /* queue_h */
