// written by
// Aravind Reddy V

// Program to print maximum number of files that can
// be opened by a process
// and size of pipe's circular buffer.

// before any includes. For F_GETPIPE_SZ
// https://stackoverflow.com/questions/25411892/f-setpipe-sz-undeclared
#define _GNU_SOURCE

// for fcntl
#include <unistd.h>
#include <fcntl.h>

// for open
#include <sys/types.h>
#include <sys/stat.h>

// for getrlimit - http://man7.org/linux/man-pages/man2/getrlimit.2.html
#include <sys/time.h>
#include <sys/resource.h>

// for errno
#include <errno.h>
#include <string.h>

// for printf
#include <stdio.h>


int main() {
    
    struct rlimit limits;
    getrlimit(RLIMIT_NOFILE, &limits);
    
    printf("Soft limit: %u bytes\nHard limit: %u bytes\n", (unsigned int) limits.rlim_cur, (unsigned int) limits.rlim_max);
    
    const char* fifo = "/tmp/23.fifo";
    if(mkfifo(fifo, 0666) < 0 && errno != EEXIST) {
	    printf("Error in mkfifo: %s\n", strerror(errno));
	}
	
	// because open blocks when fifo is not _also_ open for writing
	int fifo_fd = open(fifo, O_RDONLY | O_NONBLOCK);
	
	printf("Pipe buffer size is %ld bytes.\n", (long) fcntl(fifo_fd, F_GETPIPE_SZ));
	close(fifo_fd);
	
	
	
	
	
}
