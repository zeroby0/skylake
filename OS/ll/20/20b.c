// Written by Aravind Reddy V

// programs one way communicating via FIFO


// reader program

#include <errno.h>
#include <string.h>


#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

int main() {
    const char* fifo = "/tmp/20.fifo";
	int fifo_fd = open(fifo, O_RDONLY);
	// so, apparently, opening mkfefoed fifo blocks until it's also opened for writing.
	// so, pass O_RDONLY | O_NONBLOCK instead.
	if(fifo_fd < 0) { printf("Error in open fifo 1: %s\n", strerror(errno)); exit(-1); }
	
    char buffer[80];
	read(fifo_fd, buffer, sizeof(buffer));
	printf("%s", buffer);
	close(fifo_fd);
}