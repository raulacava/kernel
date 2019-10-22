#include "queue.h"
//
void push(queue *first, queue *last, int v) {
	queue new;
	new = (queue)malloc(sizeof(node));
	new->valor = v;
	new->next = NULL;
	if(*last) (*last)->next = new;
	*last = new;
	if(!*first) *first = new;
}
//
int pop(queue *first, queue *last) {
	queue element;
	int v;
	element = *first;
	if(!element)
		return 0;
	*first = element->next;
	v = element->valor;
	free(element);
	if(!*first)
		*last = NULL;
	return v;
}
