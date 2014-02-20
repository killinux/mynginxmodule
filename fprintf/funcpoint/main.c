#include <stdio.h>
#include <stdlib.h>
int test1(int a){
	printf("test1 function %d",a);
}
int default_func(int a){
	printf("default_func %d",a);
}

int main(int argc,char* argv){
	int (* myfunc)(int)=default_func;
	int c=(* myfunc)(1);
	
}
