/*
 * main.c
 *
 *  Created on: 2012-4-23
 *   Author: huangjacky
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define null NULL;

int hexchar2int(char);

/**
 * 对src进行url解码
 *param src char* urlencode后的字符串形式
 *return null: 字符串src的形式不对，否则 解析成功后的字符串
 */
char* urldecode(char *src){
    int len = strlen(src);
    if (len % 3) //位数不对
        return NULL;
    int count = len / 3;
    char *dst = (char *)malloc(sizeof(char) * (count+1));
    if (! dst ) // 分配空间失败
        return null;
    //节约空间，直接用变量len和count来充当临时变量
    int flag = 1;
    char *dst1 = dst;
    while(*src){//字符串没有结束
        if ( *src == '%'){//进入解析状态
            src++;
            len = hexchar2int(*src);
            src++;
            count = hexchar2int(*src);
            if (count == -1 || len == -1){//判断字符转换成的整数是否有效
                flag = 0;
                break;
            }
            *dst1++ =(char)( (len << 4) + count);//存储到目的字符串
        }else{
            flag = 0;
            break;
        }
        src++;
    }
    if (!flag){//如果解析过程中出现了错误
        free(dst);
        return null;
    }
    *dst1 = 0;//字符串的末尾加上\0
    return dst;
}
/**
 *将hex字符转换成对应的整数
 *return 0~15：转换成功，-1:表示c 不是 hexchar
 */
int hexchar2int(char c){
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else
        return -1;
}

int main(){
   // char *s = "%48%4d%20%46%3E";
    char *s = "ls%20-l%20%3Eabc";
    printf("s is : %s\r\n", s);
    char *d = urldecode(s);
    if(d){
        printf("decode is: %s \r\n", d);
        free(d);
    }
    printf("now s is : %s",s);
    return 0;
}
