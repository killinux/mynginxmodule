#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
int main( void ) 
{ 
    FILE   *thisstream; 
    u_char  * thisbuf; 
    thisbuf= (u_char *)malloc(10240*sizeof(u_char)); 
    memset( thisbuf, 0, 10240*sizeof(u_char));
    char * haoout;
    haoout=(char *)malloc(1024*sizeof(char));
    strcpy(haoout,"ls -l");

    thisstream = popen( haoout, "r" ); 
    fread( thisbuf, sizeof(u_char), 10240, thisstream);

    printf("this is :%s",thisbuf);
    pclose( thisstream );  
    return 0;
}   
