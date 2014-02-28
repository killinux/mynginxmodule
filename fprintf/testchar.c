#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char* argv[]){
//	char *mycmd="ls HTTP/1.1";
    //char mycmd[255] ="ls%20-l HTTP/1.1";// "abc d 333";
    char mycmd[255] ={"0"};// "abc d 333";
    char *mychar = (char *) malloc( sizeof(char)*255 );
    mychar="ls%20-l HTTP/1.1";
    strcpy(mycmd,mychar);
    //char *mycmd;
    //mycmd ="ls%20-l HTTP/1.1";// "abc d 333";
    char *abc;
    abc=strtok(mycmd," "); 
    //printf(" mycmd %s",mycmd);
    u_char *uu= (u_char *) malloc( sizeof(char)*255 ); 
    strcpy(uu,abc);
    printf("uu:%s\n",uu);
    if(abc){
        printf("abc:%s\n",abc);
    }
    //printf(" mycmd %s",abc);
    abc = strtok(NULL, " ");
    if (abc) printf("end:%s\n", abc);
   // system(mycmd);    
}
