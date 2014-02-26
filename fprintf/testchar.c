#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char* argv[]){
//	char *mycmd="ls HTTP/1.1";
    char mycmd[16] = "abc d";
    char *abc;
    abc=strtok(mycmd," "); 
    //printf(" mycmd %s",mycmd);
    if(abc){
        printf("abc:%s",abc);
    }
    //printf(" mycmd %s",abc);
   // system(mycmd);    
}
