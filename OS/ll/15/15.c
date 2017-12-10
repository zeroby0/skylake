// Aravind Reddy V
// from list of lab excercises
// OS sem 5

// Simple program to send data from parent to a child process


#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {
	char* fifo = "./15.fifo";
	mkfifo(fifo, 0666);

	int cpid = fork();

	if(cpid == 0) { // Child process
		char buffer[80];
		int fifo_read = open(fifo, O_RDONLY);
		read(fifo_read, buffer, 80);
		close(fifo_read);
		printf("\n@child: Message from @parent: %s", buffer);
		exit(EXIT_SUCCESS);
	}
	else { // Parent process
		char buffer[80];
		int fifo_write = open(fifo, O_WRONLY);
		printf("@parent: Message to be sent: ");
		fgets(buffer, 80, stdin);

		write(fifo_write, buffer, strlen(buffer) + 1);
		close(fifo_write);

		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	return 0;

}