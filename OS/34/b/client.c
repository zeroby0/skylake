// Written by Aravind Reddy V


// Communicate between two machines using sockets.

// ಠ_ಠ

#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>


#define PORT 8085

void pex(const char* message) {
    // print error and exit.
    perror(message);
    exit(EXIT_FAILURE);
}

int create_socket(char* server_addr) {
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket.");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in server_address;
    
    memset(&server_address, '0', sizeof(server_address));
  
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    
    if(inet_pton(AF_INET, server_addr, &server_address.sin_addr)<=0) {
        perror("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
  
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    
    return sockfd;
}


int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("server IP supplied.\n");
        exit(EXIT_FAILURE);
    }
    int sockfd;
    sockfd = create_socket(argv[1]);
    
    char message_buffer[1028]; // extra 4 bytes
    
    memset(message_buffer, 0, sizeof(message_buffer));
    scanf("%s", message_buffer);

    
    if(send(sockfd, message_buffer, strlen(message_buffer) * sizeof(char), 0) == -1) pex("Error transmitting to server.");
    memset(message_buffer, 0, sizeof(message_buffer));
    if(recv(sockfd, message_buffer, 1024 * sizeof(char), 0) == -1) pex("Error recieving from server.");
    printf("From server: %s\n", message_buffer);
}

