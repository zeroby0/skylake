// Written by
// Aravind Reddy V

// Creates a message queue,
// prints the key and the message queue ID.

// Link with -lrt

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// for errno
#include <errno.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

// for open
#include <fcntl.h>
#include <sys/stat.h>

// for close
#include <unistd.h>

#include <time.h>

void printTime(char* message, time_t * timedata) {
    printf(message, "Yesterday");
    return;
    
    printf("%d\n", timedata);
    struct tm* timeEpoch = localtime(timedata);
    printf("%d\n", timeEpoch);
    
    char buf[80];
    strftime(buf, 70, "%Y-%m-%d %H:%M:%S", timeEpoch);
    
    printf(message, buf);
    
}

int main() {

    
    key_t key = ftok("/tmp/24.messagequeue", 'a');
    if(key == -1) {
        printf("Error in ftok: %s\n", strerror(errno));
        exit(-1);
    }
    
    printf("Message Queue Key: %d\n", (int) key);
    
    // The msgget() system call returns the System V message queue identifier associated with the value of the key argument.
    // https://forums.gentoo.org/viewtopic-t-579973-start-0.html
    int messageQueueID = msgget(key, IPC_CREAT | 0600);
    if (messageQueueID == -1) {
         printf("Error in msgget: %s\n", strerror(errno));
         exit(-1);
    }
    printf("Message Queue ID: %d\n", messageQueueID);
    
    // The third argument is ignored
    if(msgctl(messageQueueID, IPC_RMID, NULL) == -1) {
        printf("Cannot remove message queue: %s\n", strerror(errno));
        exit(-1);
    }

    exit(0);
    
    
    
}
