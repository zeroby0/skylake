#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/ipc.h>
#include <sys/sem.h>   
#include <stdlib.h>    

void f()
{
	printf("Hello world!\n");
	
}

int main()
{	
	int ret;
	struct itimerval value;
	
	value.it_value.tv_sec=10;
	value.it_value.tv_usec=10;
	
	ret=setitimer(ITIMER_REAL,&value,0);
	
	printf("%d\n",ret);
	signal(14,f);
	sleep(10);
}
