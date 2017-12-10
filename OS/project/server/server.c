// Written by Aravind Reddy V

// Concurrent Server to communicate between two machines via sockets.

// ಠ_ಠ

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>

#include <semaphore.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>


int PORT = 8085;
char* TICKETDB = "./ticketdb"
// #define TICKETDB "./ticketdb"
// #define PORT 8085

#include "socket.c"
#include "ticket.c"





int id = 0;

int main(int argc, char* argv[]) {
    struct sockaddr_in address;
    int sockfd = createSocket(&address);
    int connectionfd;
    
    int* new_fd; // for pthread
    while(1) {
        connectionfd = createConnection(sockfd, &address);
        id++;
        
        pthread_t handler_thread;
        new_fd = (int *)malloc(sizeof(int));
        *new_fd = connectionfd;
        
        if(pthread_create(&handler_thread, NULL, client_handler, (void *) new_fd) != 0)pex("Error in creating thread.");
        
    }
}