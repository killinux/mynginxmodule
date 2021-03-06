#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "pthread.h"
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;
void * process(void * arg)
{
  int i;
  fprintf(stderr, "Starting process %s\n", (char *) arg);
   pthread_mutex_lock(&mymutex);
  for (i = 0; i < 100; i++) {
       write(1, (char *) arg, 1);
//      fprintf(stdout, (char *) arg, 1);
  }
  pthread_mutex_unlock(&mymutex); 
  return NULL;
}
int hello(){
	printf("hello");
	return 1;
}
int main()
{
  int retcode;
  pthread_t th_a, th_b;
  void * retval;

  retcode = pthread_create(&th_a, NULL, process, "a");
  if (retcode != 0) fprintf(stderr, "create a failed %d\n", retcode);

  retcode = pthread_create(&th_b, NULL, process, "b");
  if (retcode != 0) fprintf(stderr, "create b failed %d\n", retcode);

  retcode = pthread_join(th_a, &retval);
  if (retcode != 0) fprintf(stderr, "join a failed %d\n", retcode);

  retcode = pthread_join(th_b, &retval);
  if (retcode != 0) fprintf(stderr, "join b failed %d\n", retcode);

  return 0;
}
