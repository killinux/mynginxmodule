#include <string.h>
#include <stdio.h>
int main(void)
{
    char buf[512] ; 
   // sscanf("123456 ", "%4s", buf);
//    sscanf("123456abcdedfBCDEF", "%[1-9a-z]", buf); 
//    sscanf("123456abcdedfBCDEF","%[^A-Z]", buf); 
//sscanf("iios/12DDWDFF@122", "%*[^/]/%[^@]", buf); 
sscanf("hello, world", "%*s%s", buf); 
    printf("%s\n", buf); 
    return 0;
}
