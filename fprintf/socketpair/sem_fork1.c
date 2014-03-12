#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc,char *argv[])
{
    int fd,i,count =0,nloop=10,zero=0,*ptr;
    sem_t mutex;
    fd = open("log.txt",O_RDWR | O_CREAT,S_IRWXU);
    write(fd,&zero,sizeof(int));
    ptr = mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    if(sem_init(&mutex,1,1) < 0)
        exit(0);
    if(fork()==0)
    {
            sem_wait(&mutex);
            printf("child:%d\n",(*ptr)++);
            fflush(stdout); 
            sem_post(&mutex);
            printf("child:%d\n",(*ptr)++);
        exit(0);
    }
    sem_wait(&mutex);
    printf("Parent:%d\n",(*ptr)++);
    fflush(stdout); 
    sem_post(&mutex);
    printf("Parent:%d\n",(*ptr)++);
    //sleep(2);
    return 0;
}
