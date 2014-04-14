#include <stdio.h>  
#include "hao.h"  
int heihei(){  
    test2();  
}  
  
int haha(){  
    heihei();  
    printf("haha this is haha\n");  
}  
int main()  
{  
  heihei();  
  haha();  
  printf("Hello World\n");  
  return 0;  
}  
