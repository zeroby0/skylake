// Written by
// Aravind Reddy V

// Remove a message queue

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

static void setperm_mq(int mqid, unsigned short perms) {
    struct msqid_ds settings;
    
    if(msgctl(mqid, IPC_STAT, &settings) == -1) {
        perror("Error in msgctl get settings.");
        exit(EXIT_FAILURE);
    }
    
    settings.msg_perm.mode = perms;
    
    if(msgctl(mqid, IPC_SET, &settings) == -1) {
        perror("Error in msgctl set settings.");
        exit(EXIT_FAILURE);
    }
}

static void rmid_mq(int mqid) {
    // third argument is removed
    if(msgctl(mqid, IPC_RMID, NULL) == -1) {
        perror("Error in removing message queue.");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    int mqkey = 1245;
    int mqid = msgget(mqkey, IPC_CREAT | 0666);
    if(mqid == -1) {
        perror("Error in msgget create.");
        exit(EXIT_FAILURE);
    }
    
    printf("MQ ID %d\n", mqid);
    
    int msgtype = 1;
    
    if(!strcmp(argv[1], "-s") && argc == 3)                       send_message(mqid, argv[2], msgtype);
    else if(!strcmp(argv[1], "-r"))                               recv_message(mqid, msgtype);
    else if(!strcmp(argv[1], "-p") && argc == 3)                  setperm_mq(mqid, strtol(argv[2], NULL, 8) );
    else if(!strcmp(argv[1], "-d"))                               rmid_mq(mqid);
}

