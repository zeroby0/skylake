#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

#include <sys/types.h>  // for msgget
#include <sys/ipc.h>
#include <sys/msg.h>

#include <errno.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>



int main() {
    mqd_t queueDescriptor;
    
    struct mq_attr attr;
    
    key_t queueKey = ftok("/home/aravind/Skylake/OS/messageQueue_24", 'b');
    
    attr.mq_flags = O_NONBLOCK; // 0 or O_NONBLOCK makes queue operations non blocking
    attr.mq_maxmsg = 10; // Maximum number of messages per queue
    attr.mq_msgsize = 256; // Maximum size of one message
    attr.mq_curmsgs = 0; // Number of messages currently in queue. Runtime updated
    
    // /Name is required for key name
    if ((queueDescriptor = mq_open ("/home/aravind/Skylake/OS/messageQueue_24", O_RDONLY | O_CREAT, 0777, &attr)) == -1) {
        printf("Error in opening/creating queue: %s\n", strerror(errno));
        exit (1);
    }
    
    printf("Message queue %d created. Key = %d\n", queueDescriptor, queueKey);
    
    int queueID;
    if((queueID = msgget(queueDescriptor, 0777)) == -1) {
        printf("Error in getting queue ID: %s\n", strerror(errno));
        exit(1);
    }
    
    
    
    
    
}
