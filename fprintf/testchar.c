#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char* argv[]){
//	char *mycmd="ls HTTP/1.1";
    char mycmd[255] ="ls%20-l HTTP/1.1";// "abc d 333";
    char *abc;
    abc=strtok(mycmd," "); 
    //printf(" mycmd %s",mycmd);
    if(abc){
        printf("abc:%s\n",abc);
    }
    //printf(" mycmd %s",abc);
    abc = strtok(NULL, " ");
    if (abc) printf("end:%s\n", abc);
   // system(mycmd);    
}
