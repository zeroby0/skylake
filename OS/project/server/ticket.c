extern char* TICKETDB;


#define SEMA_NAME "/semname"

static sem_t* create_sem() {
    sem_t* semaphoreAddr;
    if((semaphoreAddr = sem_open(SEMA_NAME, O_CREAT | O_RDWR)) == SEM_FAILED) {
        perror("Error in sem_open create.");
        exit(EXIT_FAILURE);
    }
    
    return semaphoreAddr;
}

static void post_sem(sem_t* semaphore) { // unlock
    if(sem_post(semaphore) == -1) {
        perror("Error in sem_post.");
        exit(EXIT_FAILURE);
    }
}

static void wait_sem(sem_t* semaphore) { // lock
    if(sem_wait(semaphore) == -1) {
        perror("Error in sem_wait.");
        exit(EXIT_FAILURE);
    }
}

int incrementTicket(const char* ticketDB) {
    int fd = open(ticketDB, O_RDONLY);
        char current;
        if( read(fd, &current, sizeof(current)) < 0) {
            perror("Error in read or premature endoffile.");
            exit(EXIT_FAILURE);
        }
    close(fd);
    
    printf("%c\n", current);
    
    fd = open(ticketDB, O_WRONLY);
        current = current + 1;
        if( write(fd, &current, sizeof(current)) < 0) {
            perror("Error in write or nothing written.");
            exit(EXIT_FAILURE);
        }
    close(fd);
    
    return current;
}

