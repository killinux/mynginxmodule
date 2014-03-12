#include <stdio.h>
#include <linux/sem.h>
#include <sys/types.h>
#include <stdlib.h>
#define MAX_RESOURCE 0
//进程间通信还是不好使
int main()
{
    key_t key;
    int semid, semval;
    struct sembuf bufred = {0, -1, IPC_NOWAIT};//-1 代表每次给资源减1
    struct sembuf bufadd = {0, 1, IPC_NOWAIT};//-1 代表每次给资源add1
    union semun semopts;

    if((key = ftok(".", 22))== -1) //获取键值
    {
        perror("ftok error!\n");
        exit(1);
    }
    if((semid = semget(key,1, IPC_CREAT)) == -1)//创建打开信号集，信号集包含信号个数为1
    {
        perror("semget error");
        exit(1);
    }
    semopts.val = MAX_RESOURCE;
    if(semval =(semctl(semid, 0, SETVAL, semopts)) == -1)//设置index为0的信号 信号值为 MAX_RESOURCE， 成功返回0，失败返回-1
    {
        perror("semctl error");
        exit(1);
    }
   //------------ 
    pid_t childpid;
    int status;
    int retval;
    childpid = fork();
    if ( -1 == childpid )
    {   
        perror( "fork()" );
        exit( EXIT_FAILURE );
    }   
    else if ( 0 == childpid )
    {   
        puts( "In child process" );
        if(semop(semid, &bufred, 1) == -1) //执行后资源数减1
        {                                                                                                                                                                  
            perror("semop error 2");
            exit(1);                                                                                                                                                   
        }
        
        if((semval = semctl(semid, 0, GETVAL, 0)) == -1)//获取现有资源，成功返回现有资源个数
        {
            perror("semctl error");
            exit(1);
        }
        printf("semval3 = %d\n", semval);
   //     sleep( 10 );//让子进程睡眠，看看父进程的行为
        puts("end child process");                                                                                                                     
        exit(EXIT_SUCCESS);
    }   
    else
    {   
        //该while语句到资源数为0 因为buf设置为IPC_NOWAIT，则出现semop错误，程序退出，因为该资源以为0 ，无法在申请  
        if(semop(semid, &bufadd, 1) == -1) //执行后资源数减1
        {
            perror("semop error 1");
            exit(1);
        }
        if((semval = semctl(semid, 0, GETVAL, 0)) == -1)//获取现有资源，成功返回现有资源个数
        {
            perror("semctl error");
            exit(1);
        }
        printf("semval2 = %d\n", semval);//输出现有资源
        printf("in parent process %d\n",getpid());
   //     sleep( 5 );
        int rr= waitpid( childpid, &status, WUNTRACED );
        printf("result:%d\n",rr);
        printf("result:%.8x\n",rr);
    }   

    exit(0);
}
