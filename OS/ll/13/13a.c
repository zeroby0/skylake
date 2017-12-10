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

void my_handler ()
{
	 printf ("I got SIGSTOP\n");
}

int main ( void ) 
{
	//Catch SIGSTOP
	printf("pid: %d\n", getpid());
	signal(SIGSTOP,my_handler);
    printf ("Catching SIGSTOP\n");
    getchar();
}
