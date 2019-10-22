#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
   int valor;
   struct _node *next;
} node;

typedef node* queue;

// Declare functions:
/* Funciones con colas: */
void push(queue *first, queue *last, int v);
int pop(queue *first, queue *last);
#endif /* queue_h */
