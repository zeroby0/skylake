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

void my_handler (int sig)
{
	 printf ("I got SIGINT, number %d\n", sig);
}

int main ( void ) 
{
    struct sigaction my_action;
	//Catch SIGINT 
	my_action.sa_handler = my_handler;
    sigaction (SIGINT, &my_action, NULL);
    printf ("Catching SIGINT\n");
    sleep(10);
    printf (" No SIGINT within 10 seconds\n");

}
