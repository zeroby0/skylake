// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdio.h>

// int main() {
// 	if(!fork()) {
// 		printf("ch: PPID = %d\n", getppid());
// 		sleep(3);
// 		printf("ch: PPID = %d\n", getppid());
// 	} else {
// 		printf("pr: PID = %d\n", getpid());
// 		sleep(1);
// 		printf("pr: quittingt\n");
// 	}
// }

#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("PID of current process %d\n\n", getpid());

	printf("Calling fork()\n\n");
	int fork_n = fork();
	printf("Fork returned %d\n", fork_n);

	if (fork_n)
	{
		printf("    Parent Process. Child PID = %d\n", fork_n);
		printf("    PID returnedby getpid() = %d\n", getpid());
		printf("\n");
		// wait();
	} else {
		printf("    Child Process. Parent PID = %d\n", getppid());
		// By the time child is executed, parent finishes execution and
		// child is assigned to init.d
		// uncomment wait(); in above block to get parent value

		printf("    PID returnedby getpid() = %d\n", getpid());
	}

	printf("\n");
}