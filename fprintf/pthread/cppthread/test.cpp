#include <iostream>
#include <pthread.h>
using namespace std;
class threadclass
{
    public:
        threadclass();
    private:
        static int a ;
        pthread_t reader;
        static void * thisfunc(void *arg);

};
int threadclass::a = 1;

threadclass::threadclass()
{ 
    pthread_create(&reader,NULL,thisfunc,NULL);

    cout << "main thread\n" << endl;
}

void * threadclass::thisfunc(void *arg)
{
    cout << a << endl;
    return NULL;
}

int main()
{
    threadclass d;
    return 0 ;
}
