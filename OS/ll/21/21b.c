// Written by Aravind Reddy V

// programs one way communicating via FIFO

// First read and then write

#include <errno.h>
#include <string.h>


#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

int main() {
	// if (mknod("./20.fifo", S_IFIFO, 0) == -1) {
	// 	printf("Error in mknod: %s\n", strerror(errno));
	// 	if(errno != EEXIST) exit(-1);
	// }

	int fifo_fd = open("/tmp/21.fifo", O_RDONLY);
	if(fifo_fd < 0) { printf("Error in open fifo 1: %s\n", strerror(errno)); exit(-1); }
    char buffer[80];
	read(fifo_fd, buffer, sizeof(buffer));
	printf("%s", buffer);
	close(fifo_fd);
	
	char* message = "Hello from 2\n";

	fifo_fd = open("/tmp/21.fifo", O_WRONLY);
	if(fifo_fd < 0) { printf("Error in open fifo 2: %s\n", strerror(errno)); exit(-1); }
	write(fifo_fd, message, strlen(message) + 1);
	close(fifo_fd);
}