#include<stdio.h>
#include<string.h>
#include <stdlib.h>
int main()
{
	char *a = (char*)malloc(sizeof("12345"));
	char *b = (char*)malloc(sizeof("1234"));
	char *c= "ccccc";
	char *d= "cddcc";

	strcpy(a,"12345");
	strcpy(b,"1234");
	strcat(b,"aaa");
	

	char * result=(char *)malloc((strlen(c)+strlen(d))*sizeof(char));

	printf("%s %s size:%d\n",a,b,strlen(a));
	printf("%s %s size:%d\n",a,b,strlen(strcpy(a,b)));
	printf("%s %s size:%d\n",a,result,strlen(result));

	int len=strlen(c)+strlen(d)+1;
	char * result1=(char *)malloc(len);
	snprintf(result1, len, "%s%s", c,a);
	printf("%s result1: %s size:%d\n",a,result1,strlen(result1));
	return 0;
}
