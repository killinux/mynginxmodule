#include <stdio.h>
extern char a[];
//http://baike.baidu.com/link?url=e7wNp8nSE9xRImYzdxj8g6OP4glBw4YOsy-pORL2-6A8mcXW92xkFmXizGw12NWS
//但是定义只能出现在一处。也就是说，不管是int a;还是int a=0;都只能出现一次，而那个extern int a可以出现很多次。
int main(){
	printf("aaaa:%s",&a);
}
