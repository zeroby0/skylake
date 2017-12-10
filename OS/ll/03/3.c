#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h> 


int main()
{	
	struct rlimit r;
	
	getrlimit(RLIMIT_NOFILE,&r);
	printf("Default limit on number of file descriptors is : %lld\n", (long long int)r.rlim_cur); 
	
	r.rlim_cur=4; //soft limit, can be changed by any user
	setrlimit (RLIMIT_NOFILE, &r); 
	
	getrlimit(RLIMIT_NOFILE,&r);
	printf("New limit on number of file descriptors is : %lld\n", (long long int)r.rlim_cur); 
}


