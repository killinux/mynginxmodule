#ifndef STACK
#define STACK

#define elem_t char

#define T Stack_T
#define status int
#define  ERROR 0
#define OK 1

typedef struct T T;

T* init_stack(T* stack);
int stack_empty(T* stack);
status empty_stack(T* stacK);
status stack_push(T* stack, elem_t elem);
elem_t stack_pop(T* stack, elem_t *elem);

#undef T

#endif 

