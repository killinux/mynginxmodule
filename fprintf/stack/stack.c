#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define T Stack_T

#define INIT_SIZE 20
#define INCRECEMENT 20

struct T{
    
    elem_t *base, *top;
    int size;
};

T* init_stack(T* stack)
{
    stack = (T*)malloc(sizeof(stack) );
    if (!stack) exit(0);

    stack->base = (elem_t*)malloc(INIT_SIZE*sizeof(elem_t) );   
printf("base: %d\n", stack->base);
    stack->top = stack->base;
    stack->size = INIT_SIZE;
printf("init_base: %d\n", stack->base);
    
    return(stack);
}

int stack_empty(T* stack)
{
    return(!(stack->top - stack->base) );
}

status empty_stack(T* stack)
{
    stack->top = stack->base;

    return(OK);
} 

status stack_push(T* stack, elem_t elem)
{
    assert(stack);
    
    if ((stack->top - stack->base) >= stack->size )
    {
printf("size:%d\n", stack->size);
printf("top:%d\n", stack->top);
printf("base: %d\n", stack->base);
printf("len: %d\n", sizeof(elem_t)*stack->size+INCRECEMENT);
        stack->base = (elem_t*)realloc(stack->base,  
            sizeof(elem_t) * (stack->size+INCRECEMENT) );
        if (!stack->base)
            exit(0);
        stack->top = stack->base + stack->size;
        stack->size += INCRECEMENT;
    }
    
    *stack->top++ = elem;

    return(OK);
}

elem_t stack_pop(T* stack, elem_t* elem)
{
    assert(stack);
    if (!stack_empty(stack) )
    {
        *elem = *--stack->top;
printf(":%c\n", *elem);
printf("elem-:%c\n", *stack->top);
    }
    else
        return(ERROR);
    return(*elem);
}

elem_t get_top(T* stack, elem_t* elem)
{
    assert(stack);
    
    if (! stack_empty(stack))
        *elem = *(stack->top - 1);
    else 
        return(ERROR);

    return(*elem);
}

status stack_free(T *stack)
{
    assert(stack);
    free(stack->base);
    free(stack);

    return(OK);
}

