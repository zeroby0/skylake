// Written by
// Aravind Reddy V

// program to:
// a. write some data to the shared memory
// b. attach with O_RDONLY and check whether you are able to overwrite.
// c. detach the shared memory
// d. remove the shared memory

// link with -lrt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

static void* create_shm(int size, int* rem_shmid) {
    int skey = 1285;
    
    int shmid;
    
    if ((shmid = shmget(skey, size, 0644 | IPC_CREAT)) == -1) {
        perror("Error in shmget.");
        exit(EXIT_FAILURE);
    }
    
    void* pointer = shmat(shmid, NULL, 0);
    // void* pointer = shmat(shmid, NULL, SHM_RDONLY);
    if(pointer == (void*) -1) {
        perror("Error in shmat");
        exit(EXIT_FAILURE);
    }
    
    *rem_shmid = shmid;
    return pointer;
}

static void remove_shm(void* shm, int shmid) {
    if(shmdt(shm) == -1) {
       perror("Error in shmdt.");
       exit(EXIT_FAILURE);
    }
    
    if(shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Error in shmctl destroy.");
        exit(EXIT_FAILURE);
    }
}

static void write_shm(void* shm, void* message, int size) {
    memcpy(shm, message, size);
}

static void read_shm(void* shm, void* buffer, int size) {
    memcpy(buffer, shm, size);
    printf("Message read: %s\n", (char*) buffer);
}



int main(int argc, char* argv[]) {
    // write failed with segfault when writing with readonly
    int shmid;
    char* shmem = create_shm(256, &shmid);
    
    char* message = "HEllo!!";
    char retr[100];
    
    if(!strcmp(argv[1], "-s"))                                    write_shm(shmem, message, strlen(message) + 1);
    else if(!strcmp(argv[1], "-r"))                               read_shm(shmem, retr, strlen(message) + 1);
    else if(!strcmp(argv[1], "-d"))                               remove_shm(shmem, shmid);

}

