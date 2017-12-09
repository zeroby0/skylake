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

int main ( void ) 
{
	struct sigaction my_action;
	
//Ignore SIGINT 

   my_action.sa_handler = SIG_IGN;
   sigaction (SIGINT, &my_action, NULL);
   printf ("Ignoring SIGINT\n");
   sleep(3);
   printf (" Sleep is over\n"); 

//Default action 

   my_action.sa_handler = SIG_DFL;
   sigaction (SIGINT, &my_action, NULL);
   sleep(3);
   printf ("No SIGINT within 3 seconds\n"); 
}
