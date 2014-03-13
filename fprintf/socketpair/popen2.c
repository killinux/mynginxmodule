#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
int main( void ) 
{ 
    FILE   *stream; 
    //u_char   buf[1024]; 
    u_char  * buf; 
    buf= (u_char *)malloc(1024);; 
    memset( buf, '\0', 1024 );//初始化buf,以免后面写如乱码到文件中
    stream = popen( "ls -l", "r" ); //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
    fread( buf, sizeof(char), 1024, stream); //将刚刚FILE* stream的数据流读取到buf中
    printf("this is :%s",buf);
    pclose( stream );  
    return 0;
}   
