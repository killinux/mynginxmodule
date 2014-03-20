#include <stdlib.h>
#include <stdio.h>
int main(int argc,char *argv[]){
    time_t stime,etime;
    time(&stime);
    char * str;
    str=(char *)malloc(1024*sizeof(char));
    sleep(3);
    sprintf(str, "%lld", time(0));
    printf("this is :%s\n",str);
    time(&etime);
    printf("this is :%ld\n" ,etime - stime);   
}
