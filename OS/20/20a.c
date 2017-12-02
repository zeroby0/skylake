// Written by Aravind Reddy V

// programs one way communicating via FIFO


// writer program

#include <errno.h>
#include <string.h>


#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>



int main() {
    
    const char* fifo = "/tmp/20.fifo";
    
	if(mkfifo(fifo, 0666) < 0 && errno != EEXIST) {
	    printf("Error in mkfifo: %s\n", strerror(errno));
	}

    char* message = "Hello from 1\n";
    
	int fifo_fd = open(fifo, O_WRONLY);
	if(fifo_fd < 0) printf("Error in open fifo 1: %s\n", strerror(errno));
	
	write(fifo_fd, message, strlen(message) + 1);
	
	close(fifo_fd);
}