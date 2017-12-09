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

int main()
{
	int i,j;
	i=fork();
	if(i==0) //child
	{
		j=getppid();
		printf("Child ppid before orphan: %d\n",getppid());
		kill(SIGKILL,j);
		printf("Child ppid after orphan: %d\n",getppid() ); 
	}
	
}
