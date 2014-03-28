#include <stdio.h>
#include "stack.h"

int main(int argc, char **argv)
{
    Stack_T *mystack;
    char *pargv = argv[1];

    if (argc != 2)
    {
        printf("Usag: main ...\n");
        return(0);
    }

    mystack = init_stack(mystack); 

    char c; 
    int i=0;
    while ((c =  *pargv++) != '\0')
        stack_push(mystack, c);
    while ( (stack_pop(mystack, &c) ) )
        printf("%c", c);
        
    stack_free(mystack);

    return(0);
}

