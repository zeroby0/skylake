#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
	int fork_1 = fork();
	if(!fork_1) {
		printf("ch1: sleep 5\n");
		sleep(5);
		printf("ch1: done\n");
	} else {
		if(!fork()) {
			printf("ch2: sleep 10\n");
			sleep(10);
			printf("ch2: done\n");
		} else {
			if(!fork()) {
				printf("ch3: sleep 15\n");
				sleep(15);
				printf("ch3: done\n");
			} else {
					int status;
					waitpid(fork_1, &status, 0);
					printf("Child 1 exited\n");
			}
		}
	}

}