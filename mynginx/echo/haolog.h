
#include <stdio.h>
#include <time.h>
#define DEBUG_LOG( str ) log_append_to_file("/root/hellogit/hello/graphviz/nginx/mymodule/mylog/test.log", str,__FILE__,__LINE__ );
void log_append_to_file(char* filename,char* str,char* sourceFile,int fileLine);
