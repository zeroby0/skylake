// Written by
// Aravind Reddy V

// Send and recieve messages via message queue
// -s message to Send
// -r to recieve


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <errno.h>

#define MAX_MSG_SIZE 80

struct msgbuf {
    long mtype;
    char mtext[MAX_MSG_SIZE];
};

static void send_message(int mqid, char* message, int msgtype) {
    if(strlen(message) > MAX_MSG_SIZE) {
        fprintf(stderr, "Message too long. Maximum size is %d\n", MAX_MSG_SIZE);
        exit(EXIT_FAILURE);
    }
    struct msgbuf msg;
    msg.mtype = msgtype;
    strcpy(msg.mtext, message);
    
    // msgsnd appends a copy of the message pointed, so it's okay to pass local pointer.
    if(msgsnd(mqid, (void *) &msg, MAX_MSG_SIZE, IPC_NOWAIT) == -1) {
        perror("Error in msgsnd: ");
        exit(EXIT_FAILURE);
    }
    
    printf("Sent! msg = %s\n", message);
}

static void recv_message(int mqid, int msgtype) {
    struct msgbuf msg;
    
    //  MSG_NOERROR  is  specified,  then the message text will be truncated
    // (and the truncated part will be lost) - from man page
    // if( msgrcv(mqid, (void *) &msg, MAX_MSG_SIZE, msgtype, MSG_NOERROR | IPC_NOWAIT) == -1 ) {
    if( msgrcv(mqid, (void *) &msg, MAX_MSG_SIZE, msgtype, 0) == -1 ) {
        if(errno != ENOMSG) {
            perror("Error in msgrcv.");
            exit(EXIT_FAILURE);
        }
        printf("No messages in queue.\n");
    } else {
        printf("Message: %s\n", msg.mtext);
    }
}

int main(int argc, char* argv[]) {
    int mqkey = 1234;
    int mqid = msgget(mqkey, IPC_CREAT | 0666);
    if(mqid == -1) {
        perror("Error in msgget.");
        exit(EXIT_FAILURE);
    }
    
    int msgtype = 1;
    if(!strcmp(argv[1], "-s") && argc == 3) {
        send_message(mqid, argv[2], msgtype);
    }
    else if(!strcmp(argv[1], "-r")) recv_message(mqid, msgtype);
}

