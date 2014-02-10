#include <stdlib.h>
#include <stdio.h>
int main(int args,char* argv){
	char *pT;
	char t[]="bah";
	pT=&t;
	*pT++;
	putchar(*pT);
}
