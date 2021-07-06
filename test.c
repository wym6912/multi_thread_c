#include "threadpool.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct call
{
    int x;
    char *y;
}call;

int real_fun(int x, char *y)
{
    puts(y);
    return x;
}

void* mytask(void *arg)
{
    printf("thread %d is working on task %d, another is %s\n", (int)pthread_self(), ((call *)arg) -> x, ((call *)arg) -> y);
    real_fun(((call *)arg) -> x, ((call *) arg) -> y);
    sleep(5);
    printf("Wake up %d\n", (int)pthread_self());
    free(((call *)arg) -> y);
    free(arg);
    return NULL;
}

//测试代码
int main(void)
{
    threadpool_t pool;
    //初始化线程池，最多三个线程
    threadpool_init(&pool, 3);
    int i, j;
    call a;
    //创建十个任务
    for(i=0; i < 12; i++)
    {
        call *arg = malloc(sizeof(call));
        arg -> x = i;
        arg -> y = malloc(sizeof(char) * 10);
        for(j = 0; j < 10; ++ j) arg -> y[j] = 'a' + j + i; 
        threadpool_add_task(&pool, mytask, arg);
        
    }
    threadpool_destroy(&pool);
    return 0;
}