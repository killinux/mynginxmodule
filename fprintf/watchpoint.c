#include<stdio.h>
#include<string.h>
#include <stdlib.h>
int main()
{
	char *a = (char*)malloc(sizeof("12345"));
	char *b = (char*)malloc(sizeof("1234"));

	strcpy(a,"12345");
	strcpy(b,"1234");
	strcpy(a,b);

	printf("%s %s size:%d\n",a,b,strlen(a));
	printf("%s %s size:%d\n",a,b,strlen(strcpy(a,b)));

	return 0;
}
