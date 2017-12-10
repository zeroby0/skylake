// Written by Aravind Reddy V

// programs one way communicating via FIFO

// First write and then read

#include <errno.h>
#include <string.h>


#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

int main() {
    
	if(mkfifo("/tmp/21.fifo", 0666) == -1 && errno != EEXIST) {
	    printf("Error in mkfifo: %s\n", strerror(errno));
	}

    char* message = "Hello from 1\n";
    
	int fifo_fd = open("/tmp/21.fifo", O_WRONLY);
	if(fifo_fd < 0) printf("Error in open fifo 1: %s\n", strerror(errno));
	write(fifo_fd, message, strlen(message) + 1);
	close(fifo_fd);

	fifo_fd = open("/tmp/21.fifo", O_RDONLY);
	if(fifo_fd < 0) printf("Error in open fifo 2: %s\n", strerror(errno));
	char buffer[80];
	read(fifo_fd, buffer, sizeof(buffer));
	printf("%s", buffer);
	close(fifo_fd);



}