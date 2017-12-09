#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	if (!fork())
	{ // child process
		// sleep(1);
		printf("ch: PID = %d\n", getpid());

		printf("run:\n\nps axo stat,ppid,pid,comm | grep %d\n", getpid());
		
	} else { // parent process
		printf("Waiting for 30 seconds\n");
		sleep(30);
		
		
	} printf("\n");
}