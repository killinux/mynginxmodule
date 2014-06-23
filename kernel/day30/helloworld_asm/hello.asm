; hello.asm 
section .data            ; 数据段声明 
        msg db "Hello, world!", 0xA     ; 要输出的字符串 
        len equ $ - msg                 ; 字串长度 

section .text            ; 代码段声明 
global _start            ; 指定入口函数 
_start:                  ; 在屏幕上显示一个字符串 
;1、设置系统调用号4，采用软中断80可以陷入内核执行 
;所有的系统调用和对应的系统调用号都可以在/usr/include/asm/unistd.h中找到 
;4号系统调用号为write这个系统调用 
mov eax, 4       ; 系统调用号(sys_write) 

;2、设置系统调用参数 
;man 2 write 可以查看write系统调用的功能 
;write函数原型： ssize_t write(int fd,const void *buf,size_t count); 
        mov ebx, 1       ; 参数一：文件描述符(stdout) 
        mov ecx, msg     ; 参数二：要显示的字符串 
        mov edx, len     ; 参数三：字符串长度   
        int 0x80         ; 调用内核功能。软中断，陷入内核 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

        ; 退出程序 
;3、设置系统调用号1，采用软中断80可以陷入内核执行 
mov eax, 1       ; 系统调用号(sys_exit) 
;4、设置系统调用参数 
        mov ebx, 0       ; 参数一：退出代码 
        int 0x80         ; 调用内核功能 
