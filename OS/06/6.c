#include <pthread.h>
#include <stdio.h>

// link with -lpthread

void thread_func(void)
{
	printf("Thread id is %lu\n", pthread_self());
}


int main()
{
	pthread_t mythread1;
	pthread_t mythread2;
	pthread_t mythread3;
	pthread_create ( &mythread1, NULL, (void *) thread_func, NULL);
	pthread_create ( &mythread2, NULL, (void *) thread_func, NULL);
	pthread_create ( &mythread3, NULL, (void *) thread_func, NULL);
	pthread_join(mythread1,NULL);
	pthread_join(mythread2,NULL);
	pthread_join(mythread3,NULL);
}
