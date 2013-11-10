#include <stdio.h>
#include <time.h>
#define DEBUG_LOG( str ) log_append_to_file("/root/hellogit/hello/graphviz/nginx/mymodule/mylog/test.log", str,__FILE__,__LINE__ );  
void log_append_to_file(char* filename,char* str,char* sourceFile,int fileLine)
{
        time_t t;
        time(&t);
        struct tm* tp= localtime(&t);
        char now_str[100];
        strftime(now_str, 100, "%Y-%m-%d %H:%M:%S", tp);
        FILE *fo;
        fo = fopen(filename, "a");
    if (fo == 0) {
        return;
    }
        fprintf(fo, "%s %s(:%d):%s\r\n",now_str,sourceFile,fileLine, str);
        fclose(fo);
}

//int main(int argc, char **argv)
//{
///*********************define******************/
//
//        DEBUG_LOG("haoning----logmain.c");
//        printf("Hello World!\n");
//        return 0;
//} 
