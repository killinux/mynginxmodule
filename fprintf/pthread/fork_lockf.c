#include <stdio.h>
char buf[]={"check lock!\n"};
int main(int argc,char *argv[]){
    int i,p1,p2,fd;
    fd=creat("lock.dat",0644);
    write(fd,buf,20);
    while((p1=fork())==-1);	
    if(p1==0){
        lockf(fd,1,0);
        for(i=1;i<=3;i++){
            printf("child1!\n");
        }
        lockf(fd,0,0); 
    }else{
        while((p2=fork())==-1);
        if(p2==0){
            lockf(fd,1,0);
            for(i=1;i<=4;i++){
                printf("child2!\n");
            }
            lockf(fd,0,0);
        }else{
            printf("parrent!\n");
        }
    }
    close(fd);
}
