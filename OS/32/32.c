#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>


#include <semaphore.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#define TICKETDB "./ticketdb"




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

static void incrementTicket(const char* ticketDB) {
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
}

static void ticketCreation() {
    
    
    sem_t* file_sem = create_sem();
    
    char initial = 'a';
    int fd = open(TICKETDB, O_CREAT | O_RDWR, 0600);
    write(fd, &initial, sizeof(initial));
    
    post_sem(file_sem); // unlock

    if(fork()) {
        // parent
        sleep(1);
        wait_sem(file_sem); //lock
            printf("Incr in parent - 1/4\n");
            incrementTicket(TICKETDB);
            printf("done p - 1/4.\n");
        post_sem(file_sem); // unlock
        sleep(3);
        wait_sem(file_sem); //lock
            printf("Incr in parent - 2/4\n");
            incrementTicket(TICKETDB);
            printf("done p - 2/4.\n");
        post_sem(file_sem); // unlock
        sleep(5);
        wait_sem(file_sem); //lock
            printf("Incr in parent - 3/4\n");
            incrementTicket(TICKETDB);
            printf("done p - 3/4.\n");
        post_sem(file_sem); // unlock
        sleep(7);
        wait_sem(file_sem); //lock
            printf("Incr in parent - 4/4\n");
            incrementTicket(TICKETDB);
            printf("done p - 4/4.\n");
        post_sem(file_sem); // unlock
        
        close(fd);
        exit(0);
        
    } else {
        // child
        sleep(1);
        wait_sem(file_sem); //lock
            printf("Incr in child - 1/4\n");
            incrementTicket(TICKETDB);
            printf("done c - 1/4.\n");
        post_sem(file_sem); // unlock
        sleep(2);
        wait_sem(file_sem); //lock
            printf("Incr in child - 2/4\n");
            incrementTicket(TICKETDB);
            printf("done c - 2/4.\n");
        post_sem(file_sem); // unlock
        sleep(3);
        wait_sem(file_sem); //lock
            printf("Incr in child - 3/4\n");
            incrementTicket(TICKETDB);
            printf("done c - 3/4.\n");
        post_sem(file_sem); // unlock
        sleep(4);
        wait_sem(file_sem); //lock
            printf("Incr in child - 4/4\n");
            incrementTicket(TICKETDB);
            printf("done c - 4/4.\n");
        post_sem(file_sem); // unlock
        
        close(fd);
        exit(0);
    }
    
    
}




int main() {
    ticketCreation();
}