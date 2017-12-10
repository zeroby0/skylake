// Written by Aravind Reddy V

// Server to communicate between two machines via sockets.

// ಠ_ಠ

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


#define PORT 8085

void pex(const char* message) {
    // print error and exit.
    perror(message);
    exit(EXIT_FAILURE);
}


int createSocket() {
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        pex("Error creating socket.");
    }

    // reusing socket
    int optval = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)) == -1) {
        pex("Error in reusing socket.");
    }
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    if(bind(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0){
        pex("Error in binding socket.");
    }
    
    // The second argument defines the maximum length to which the queue of pending connections for sockfd may grow.
    if(listen(sockfd, 10) < 0) {
        pex("Error while listening for socket connects.");
    }
    
    return sockfd;
}

int createConnection(int sockfd) {
    int connectionfd = accept(sockfd, (struct sockaddr*) NULL, NULL);
    
    if (connectionfd == -1) {
        perror("Error while accepting client connection.");
        exit(EXIT_FAILURE);
    }
    
    return connectionfd;
}

void closeConnection(int connectionfd) {
    // shutdown and close connection
    if(shutdown(connectionfd, SHUT_RDWR) == -1) {
        perror("Error shutting down connection with client.");
        exit(EXIT_FAILURE);
    }
    
    if(close(connectionfd) == -1) {
       perror("Error closing client connection.");
       exit(EXIT_FAILURE);
    }
}


int main(int argc, char* argv[]) {
    int sockfd = createSocket();
    
    int connectionfd;
    char message[1028];
    int message_size;
    
    while(1) {
        connectionfd = createConnection(sockfd);
        
        // echo server.
        message_size = recv(connectionfd, message, sizeof(message), 0);
        
        while(message_size) {
            printf("From client: %s\n", message);
            if(message_size == -1) pex("Error while recieving message from client.");
            if(send(connectionfd, message, message_size, 0) == -1) pex("Error transmitting to client.");
            memset(message, 0, sizeof(message));
            message_size = recv(connectionfd, message, (strlen(message) + 1) * sizeof(char), 0);
        }
        if(message_size == 0) closeConnection(connectionfd);
    }
    
    
}
