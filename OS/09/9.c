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


int main () 
{
// Ignore SIGINT 
	signal (SIGINT, SIG_IGN);
	printf ("Ignoring SIGINT\n");
	sleep(3);
	printf ("No SIGINT within 3 seconds\n");

//Default action 
	signal (SIGINT, SIG_DFL);
	printf ("Default action for SIGINT\n");
	sleep(3);
	printf ("No SIGINT within 3 seconds\n");
}

