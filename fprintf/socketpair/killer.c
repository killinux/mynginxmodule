#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int main( void )
{
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
        sleep( 10 );//让子进程睡眠，看看父进程的行为
        puts("end child process");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("in parent process %d\n",getpid());
        sleep( 5 );
        //retval = kill( getpid(),SIGKILL );
        //if ( 0 == (waitpid( childpid, &status, WNOHANG )))
        int rr= waitpid( childpid, &status, WUNTRACED );
        printf("result:%d\n",rr);
        printf("result:%.8x\n",rr);
        //if ( 0 == (waitpid( childpid, &status, WUNTRACED )))
        //{
        //    printf("status: %d\n",status);
        //    retval = kill( childpid,SIGKILL );
        //    if ( retval )
        //    {
        //        puts( "kill failed." );
        //        perror( "kill" );
        //        waitpid( childpid, &status, 0 );
        //    }
        //    else
        //    {
        //        printf( "%d killed\n", childpid );
        //    }
        //    
        //}
    }
    exit(EXIT_SUCCESS);
}
