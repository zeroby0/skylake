#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

#include <semaphore.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>


#define SEMA_NAME "/semname"

static sem_t* create_sem() {
    sem_t* semaphoreAddr;
    if((semaphoreAddr = sem_open(SEMA_NAME, O_CREAT | O_RDWR)) == SEM_FAILED) {
        perror("Error in sem_open create.");
        exit(EXIT_FAILURE);
    }
    
    return semaphoreAddr;
}

static void post_sem(sem_t* semaphore) {
    if(sem_post(semaphore) == -1) {
        perror("Error in sem_post.");
        exit(EXIT_FAILURE);
    }
}

static void wait_sem(sem_t* semaphore) {
    if(sem_wait(semaphore) == -1) {
        perror("Error in sem_wait.");
        exit(EXIT_FAILURE);
    }
}

// binary semaphore is a mutex

int main() {
    sem_t* semaphore = create_sem();

    if(fork()) {
        // parent
        
        if(fork()) {
            // parent
            sleep(2);
            post_sem(semaphore);
            sleep(2);
            post_sem(semaphore);
            exit(0);
        } else {
            // child 2
            sem_wait(semaphore);
            printf("Child2 recvd. exiting.\n");
            exit(0);
        }
        
    } else {
        // child1
        sem_wait(semaphore);
        printf("Child1 recvd. exiting.\n");
        exit(0);
    }
    
}