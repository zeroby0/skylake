#include <stdio.h>
#include <sys/resource.h>

int main(int argc, char * argv[]) {
	int priority = getpriority(PRIO_PROCESS, 0);

	printf("Priority of the current thread is: %d\n\n", priority);
	printf("Use `nice -n <priority> %s` to set priority.\n", argv[0]);
	printf("Super user is required to lower priorities.\n");
}