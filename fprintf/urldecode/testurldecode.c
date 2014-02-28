#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void encodeurl(){
    int c;
    char *hex = "0123456789abcdef";
    while( (c = getchar()) != EOF ){
        if( ('a' <= c && c <= 'z')
        || ('A' <= c && c <= 'Z')
        || ('0' <= c && c <= '9') ){
            putchar(c);
        } else {
            putchar('%');
            putchar(hex[c >> 4]);
            putchar(hex[c & 15]);
        }
    }
}
void hao_urldecode(char *dest, const char *src)
{
    const char *p = src;
    char code[3] = {0};
    unsigned long ascii = 0;
    char *end = NULL;

    while(*p)
    {
        if(*p == '%')
        {
            memcpy(code, ++p, 2);
            ascii = strtoul(code, &end, 16);
            *dest++ = (char)ascii;
            p += 2;
        }
        else
            *dest++ = *p++;
    }
}

int main()
{
    char in[] = "ram%40d%20omain.tld";
    char out[sizeof in] = {0};
    hao_urldecode(out, in);
    printf("in == %s\nout == %s\n", in, out);
    return 0;
}
