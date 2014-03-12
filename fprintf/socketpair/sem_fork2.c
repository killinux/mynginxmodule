#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#define DELAY_TIME  3 /*为了突出演示效果，等待几秒*/
/*定义联合体*/
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
/*函数声明*/
int init_sem(int sem_id,int init_value);/*信号量初始化（赋值）函数*/
int del_sem(int sem_id); /*从系统中删除信号量的函数*/
int sem_p(int sem_id); /*P 操作函数*/
int sem_v(int sem_id); /*V 操作函数*/

int main(void)
{
    pid_t result;
    int sem_id;
    /* 创建一个信号量 */
    sem_id=semget(ftok(".",'a'),1,0666|IPC_CREAT);
    init_sem(sem_id,0);
    /* 调用fork()函数*/
    result=fork();
    if(result==-1)
    {
        perror("Fork\n");
    }
    else if(result==0)/*返回值为0代表子进程*/
    {
        printf("Child progress will wait for some seconds...\n");
        sleep(DELAY_TIME);/*睡眠3秒，执行父进程*/
        printf("The returned value is %d in the child progress(PID=%d)\n",result,getpid());
        sem_v(sem_id);  
    }
    else /*返回值大于0代表父进程*/
    {
        sem_p(sem_id);
        printf("The returned value is %d in the father progress(PID=%d)\n",result,getpid());
        sem_v(sem_id);
        del_sem(sem_id);
    }
    exit(0);    
}/* main() end*/

/*信号量初始化（赋值）函数*/
int init_sem(int sem_id,int init_value)
{
    union semun sem_union;
    sem_union.val=init_value;  /*init_value为初始值*/
    if(semctl(sem_id,0,SETVAL,sem_union)==-1)
    {
        perror("Initialize semaphore");
        return -1;
    }
    return 0;
}

/*从系统中删除信号量的函数*/
int del_sem(int sem_id)
{
    union semun sem_union;
    if(semctl(sem_id,0,IPC_RMID,sem_union)==-1)
    {
        perror("Delete semaphore");
        return -1;
    }
}

/*P 操作函数*/
int sem_p(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num=0;  /*信号量编号，这里单个信号量的编号应该为0*/
    sem_b.sem_op=-1; /*信号量操作，取值为-1表示P操作*/
    sem_b.sem_flg=SEM_UNDO; /*在进程没释放信号量而退出时，系统自动释放该进程中
                            未释放的信号量*/
    if(semop(sem_id,&sem_b,1)==-1)  /*进行Ｐ操作*/
    {
        perror("P operation");
        return -1;
    }
    return 0;
}

/*V 操作函数*/
int sem_v(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num=0;  /*信号量编号，这里单个信号量的编号应该为0*/
    sem_b.sem_op=1; /*信号量操作，取值为+1表示V操作*/
    sem_b.sem_flg=SEM_UNDO; /*在进程没释放信号量而退出时，系统自动释放该进程中
                            未释放的信号量*/
    if(semop(sem_id,&sem_b,1)==-1)  /*进行V 操作*/
    {
        perror("V operation");
        return -1;
    }
    return 0;
}




