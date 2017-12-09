#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

// you getting a chocolate

int main()
{	
	int ret;
	struct rlimit r;
	getrlimit(RLIMIT_NOFILE,&r);
	printf("Max file descriptors is : %lld\n", (long long int)r.rlim_cur);
	// man 2 getrlimit
}


