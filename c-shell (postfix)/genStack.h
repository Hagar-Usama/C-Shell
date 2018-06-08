#ifndef STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#endif


#ifndef STDLIB_H
#include <string.h>
#endif

#define ERROR 77566.95415


typedef struct {
  void* data;
  int top;
  int totalElements;
  int memberSize;
} Stack;

//initialize stack
void createStack(int memberSize, int totalElements , Stack *s) {
  //Stack *s = malloc(sizeof(Stack));
  s->top = -1;
  s->memberSize = memberSize;
  s->totalElements = totalElements;
  s->data = malloc(totalElements*memberSize);
  //return s;
}

// double stack size
int expandStack(Stack* s) {
  //double total capacity of the stack
  s->data = realloc(s->data, s->totalElements * 2);
  s->totalElements *= 2;
  return 0;
}

//Stack Push



int stackPush(Stack *s,  void *data) {
  //check is the stack is full
  if (s->top == s->totalElements - 1) {
    //if full, call expand function to expand the size of the stack
    expandStack(s);
  }
  s->top++;
  //calculate starting location for the new element
  void* target = (char*)s->data+(s->top*s->memberSize);
  memcpy(target, data, s->memberSize);
  return 0;
}


// stack Pop

int stackPop(Stack *s,  void *target) {
  if (s->top == -1) {
    return 0;
  }
  void* source = (char*)s->data+(s->top*s->memberSize);
  s->top--;
  memcpy(target, source, s->memberSize);
  return 1;
}




/*
int stackPop(Stack *s,  void *target) {
  if (s->top == -1) {
    return 0;
  }
  void* source = (char*)s->data+(s->top*s->memberSize);
  s->top--;
  memcpy(target, source, s->memberSize);
  return 1;
}

*/

// stack Peak >> Top
int stackTop(Stack *s,  void *target) {
  if (s->top == -1) {
    return 0;
  }
  void* source = (char*)s->data+(s->top*s->memberSize);
  memcpy(target, source, s->memberSize);
  return 1;
}

// stack destruct
int stackDestroy(Stack *s) {
  free(s->data);
  free(s);
  return 0;
}


int isStackEmpty(Stack *s) {
  return s->top == -1 ?  1 : 0;
    
  }




/*
int stackPush(Stack *s,  void *element) {
  //check is the stack is full
  if (s->top == s->totalElements - 1) {
    //if full, return 1 which would signal that the operation failed
    return 1;
  }
  s->top++;
  //calculate starting location for the new element
  void* target = (char*)s->data+(s->top*s->memberSize);
  memcpy(target, element, s->memberSize);
  return 0;
}

*/

