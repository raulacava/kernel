/*
 ============================================================================
 Name        : queueTest.c
 Author      : Noe
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//
int main() {
   queue first = NULL, last = NULL;

   push(&first, &last, 20);
   printf("Push(20)\n");
   push(&first, &last, 10);
   printf("Push(10)\n");
   printf("Pop: %d\n", pop(&first, &last));
   push(&first, &last, 40);
   printf("Push(40)\n");
   push(&first, &last, 30);
   printf("Push(30)\n");
   printf("Pop: %d\n", pop(&first,&last));
   printf("Pop: %d\n", pop(&first,&last));
   push(&first, &last, 90);
   printf("Push(90)\n");
   printf("Pop: %d\n", pop(&first,&last));
   printf("Pop: %d\n", pop(&first,&last));
   return 0;
}

