#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
int main(){
	struct timeval t1, t2;
   float elapsedTime;

    // start timer
    gettimeofday(&t1, NULL);
    int x=getpid();
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
	
	printf("time taken = %f ms\n",elapsedTime);
}