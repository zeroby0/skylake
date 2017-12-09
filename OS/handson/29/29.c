#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int x=sched_getscheduler(getpid());
	switch(x){
		case SCHED_FIFO:
		printf("SCHED_FIFO\n");
		break;
		case SCHED_OTHER:
		printf("SCHED_OTHER\n");
		break;
		
		case SCHED_RR:
		printf("SCHED_RR\n");
		break;
		default:
		printf("sorry\n");
		break;

	}
	struct sched_param sp;
	sp.sched_priority=sched_get_priority_min(SCHED_FIFO);
	sched_setscheduler(getpid(),SCHED_FIFO, &sp);
	int x2=sched_getscheduler(getpid());
	switch(x2){
		case SCHED_FIFO:
		printf("SCHED_FIFO\n");
		break;
		case SCHED_OTHER:
		printf("SCHED_OTHER\n");
		break;
		
		case SCHED_RR:
		printf("SCHED_RR\n");
		break;
		default:
		printf("sorry\n");
		break;

	}
}
