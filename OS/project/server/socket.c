;
extern char* TICKETDB;
extern int incrementTicket(const char* ticketDB);

extern int PORT;
extern int id;


static void pex(const char* message) {
    // print error and exit.
    perror(message);
    exit(EXIT_FAILURE);
}

int createSocket(struct sockaddr_in* address) {
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        pex("Error creating socket.");
    }

    // reusing socket
    int optval = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)) == -1) {
        pex("Error in reusing socket.");
    }
    
    // struct sockaddr_in address;
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons( PORT );
    
    if(bind(sockfd, (struct sockaddr *) address, sizeof(*address)) < 0){
        pex("Error in binding socket.");
    }
    
    // The second argument defines the maximum length to which the queue of pending connections for sockfd may grow.
    if(listen(sockfd, 10) < 0) {
        pex("Error while listening for socket connects.");
    }
    
    return sockfd;
}

int createConnection(int sockfd, struct sockaddr_in * address) {
    int addrlen = sizeof(*address);
    int connectionfd = accept(sockfd, (struct sockaddr*) address, (socklen_t*) &addrlen);
    
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

int process_request(char* request) {
    if(!strcmp(request, "book")) {
        int ticket_number = incrementTicket(TICKETDB);
        sprintf(request, "Your ticker number is %d.", ticket_number);
        return 1;
    }
    
    if(!strcmp(request, "exit")) {
        strcpy(request, "Done. exiting.");
        return 0;
    }
}

void* client_handler(void* connfd) {
    int connectionfd = *(int *) connfd;
    
    char message[1028];
    int message_size;
    
    // echo server.
    message_size = recv(connectionfd, message, sizeof(message), 0);
    int status;
    while(message_size) {
        printf("From client %d: %s\n", id, message);
        if(message_size == -1) pex("Error while recieving message from client.");
        
        status = process_request(message);
        
        if(send(connectionfd, message, message_size, 0) == -1) pex("Error transmitting to client.");
        printf("Sent to %d: %s\n", id, message);
        
        if(status == 0) {
            closeConnection(connectionfd);
            return NULL;
        }
        memset(message, 0, sizeof(message));
        message_size = recv(connectionfd, message, sizeof(message), 0);
    }
    
    if(message_size == 0) closeConnection(connectionfd);
}