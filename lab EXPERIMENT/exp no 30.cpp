
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* arg)
{
    printf("Inside the thread\n");
    return NULL;
}

int main()
{
    pthread_t ptid;

    pthread_create(&ptid, NULL, func, NULL);

    printf("Thread created successfully\n");

    pthread_detach(ptid);

    if (pthread_equal(ptid, pthread_self()))
        printf("Threads are equal\n");
    else
        printf("Threads are not equal\n");

    sleep(1);
    printf("Main thread ends\n");

    return 0;
}
