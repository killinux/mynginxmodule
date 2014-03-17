#include <stdio.h>
#include <stdlib.h>
int main(){
    char *urlcmd;
    urlcmd="123456 abcdedf";
    char * haoout;
    haoout=(char *)malloc(1024*sizeof(char));
    sscanf(urlcmd, "%[^ ]", haoout); 
    printf("thisis :%s\n",haoout);
}
