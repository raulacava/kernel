#include "queue.h"
//
void push(queueS *first, queueS *last, int v) {
   queueS new;
   new = (queueS)malloc(sizeof(node));
   new->value = v;
   new->next = NULL;
   if(*last) (*last)->next = new;
   *last = new;
   if(!*first) *first = new;
}
//
int pop(queueS *first, queueS *last) {
   queueS element;
   int v;
   element = *first;
   if(!element)
       return 0;
   *first = element->next;
   v = element->value;
   free(element);
   if(!*first)
       *last = NULL;
   return v;
}
