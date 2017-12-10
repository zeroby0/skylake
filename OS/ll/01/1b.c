#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>           
#include <sys/stat.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>   
#include <stdlib.h>    

void f()
{
	printf("Hello world!\n");
	
}

unsigned long long rdtsc()
{
	unsigned long long dst;
	__asm__ __volatile__("rdtsc":"=A"(dst)); // wtf
	return dst;
}

int main()
{	
	int ret;
	long long int start,end;
	start=rdtsc();
	struct itimerval value;
	value.it_value.tv_sec=0;
	value.it_value.tv_usec=0; 
	ret=setitimer(ITIMER_VIRTUAL,&value,0);
	printf("%d\n",ret);
	signal(14,f);
	end=rdtsc();
	long long s;
	s=(end-start)/0.34; //freq is 3 GHz
	printf("Difference is: %llu ns \n",s);
	
}

//countdown is when process is executing in user mode
