#include "stdio.h"
#include "stdlib.h"

// Stack to store tree nodes
// Implemented using linked lists

#ifndef DATA_TYPE
#define DATA_TYPE void *
#endif

typedef struct stk_stack_node {
  DATA_TYPE info;
  struct stk_stack_node * next;
} stk_stack_node;

typedef struct stk_stack { 
  stk_stack_node * top;
  stk_stack_node * tail;
} stk_stack ;

stk_stack * StackCreate();
void StackPush(stk_stack * theStack, DATA_TYPE newInfoPointer);
void * StackPop(stk_stack * theStack);
int StackNotEmpty(stk_stack *);

