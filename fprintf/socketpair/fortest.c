#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char* argv){
    int count;
    //   srand((unsigned) time(NULL));
    char str[255];
    for(count=0;count<5;count++){
        sprintf(str, "test%d", rand());
        printf("%s\n",str); 
    }
}
