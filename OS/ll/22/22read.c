// Written by Aravind Reddy V

// Program to wait for data to be written to fifo_fd
// waiter Program

#include <errno.h>
#include <string.h>

#include <sys/select.h>

// #include <sys/time.h>
// #include <sys/types.h>
// #include <unistd.h>
       
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/22.fifo"
#define TV_SEC 5
#define TV_USEC 0

int main() {
    // so, apparently, opening fifo blocks until it's also opened for writing.
	// so, pass O_RDONLY | O_NONBLOCK instead.
	// https://stackoverflow.com/questions/8507810/why-does-my-program-hang-when-opening-a-mkfifo-ed-pipe
    int fifo_fd = open(FIFO_FILE, O_RDONLY | O_NONBLOCK);
    if(fifo_fd < 0) printf("Error in open fifo 1: %s\n", strerror(errno));
    
    
    fd_set set; // set of file descriptors
    FD_ZERO(&set); // make all the fds in the set 0. Initialising set
    FD_SET(fifo_fd, &set); // adding fd of our fifo to the set
    
    struct timeval timeout;
    timeout.tv_sec = TV_SEC;
    timeout.tv_usec = TV_USEC;
    
    int result = select(fifo_fd + 1, &set, NULL, NULL, &timeout);
    if (result == 0) {
        printf("Timed out.\n");
    }
    else if (result < 0) {
        printf("Error occured in select: %s\n", strerror(errno));
    } else {
        printf("Data recieved.\n");
        char buffer[80];
        read(fifo_fd, buffer, sizeof(buffer));
        printf("data: %s", buffer);
    }
    
    close(fifo_fd);
    
    
}