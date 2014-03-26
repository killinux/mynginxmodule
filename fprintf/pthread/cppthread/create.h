#ifndef __CREATOR__H_
#define __CREATOR__H_

#include <stdio.h>
#include "thread.h"

class Create: public Thread
{
protected:
  void * run(void * param)
  {
    char * msg = (char*) param;
    printf ("%s\n", msg);
    //sleep(100); 可以试着取消这行注释，看看结果有什么不同。
    printf("One day past.\n");
    return NULL;
  }
};
#endif
