#include <stdio.h>
#include <pthread.h>
#define BILLION  1000000000; 

pthread_mutex_t mutex;

long long thread_count = 0;
long long n = 1000000055;
double sum = 0.0;

int turn = 0;

void* Thread_sum(void *rank)
{
    
    long my_rank = (long) rank;
    double factor;
    long long my_n = n/thread_count;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i + my_n;
    double my_sum = 0.0;

    if (my_first_i % 2 == 0) //even
        factor = 1.0;
    else // odd
        factor = -1.0;

    for (long long i = my_first_i; i<my_last_i; i++, factor = (-1)*factor)
        my_sum += factor/(2*i + 1);

    while(turn != my_rank);
    sum+= my_sum;
    turn +=1;
    return NULL;
}
int main() 
{
    scanf("%lld",&thread_count);
    pthread_t threads[thread_count];
    long t;
    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);
    for(t=0; t<thread_count; t++)
    {
        pthread_create(&threads[t], NULL, Thread_sum, t);
    }

    for(t=0;t<thread_count;t++)
    {
        pthread_join(threads[t], NULL);
    }
    printf("sum: %f \n", 4.0*sum);
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
       + ( requestEnd.tv_nsec - requestStart.tv_nsec )
       / BILLION;
    printf( "Time: %lf\n", accum );
    return 0;
}
