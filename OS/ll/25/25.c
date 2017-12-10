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
    
    
    struct msqid_ds mq_data;
    if(msgctl(messageQueueID, IPC_STAT, &mq_data) == -1){
        printf("Error in msgctl get data: %s\n", strerror(errno));
        exit(-1);
    }
    
    struct ipc_perm permissions = mq_data.msg_perm;
    // permissions in octal.
    printf("\nPermissions: %o\n", permissions.mode);
    printf("Owner UID = %d, GID = %d\n", permissions.uid, permissions.gid);
    printf("Creator UID = %d, GID = %d\n", permissions.cuid, permissions.cgid);
    
    
    printTime("\nLast message sent at %s\n", &mq_data.msg_stime);
    printTime("Last message recv at %s\n", &mq_data.msg_rtime);
    printTime("Last message changed at %s\n", &mq_data.msg_ctime);
    
    printf("\nSize of message queue is %d bytes\n", mq_data.__msg_cbytes);
    printf("Number of messages  in the queue is %d\n", mq_data.msg_qnum);
    printf("Maximum number of bytes in the queue is %d\n", mq_data.msg_qbytes);
    
    printf("\npid of msgsnd is %d\n", mq_data.msg_lspid);
    printf("pid of msgrcv is %d\n", mq_data.msg_lrpid);
    
    // The third argument is ignored
    if(msgctl(messageQueueID, IPC_RMID, NULL) == -1) {
        printf("Cannot remove message queue: %s\n", strerror(errno));
        exit(-1);
    }

    exit(0);
    
    
    
}
