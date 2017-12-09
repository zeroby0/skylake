#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
 

unsigned long long rdtsc()
{
	unsigned long long dst;
	__asm__ __volatile__("rdtsc":"=A"(dst));
	return dst;
}

int main()
{	
	int i;
	long long int start,end;
	start=rdtsc();
	for(i=0;i<100;i++)
	{
		getppid();
	}
	
	end=rdtsc();
	long long s;
	s=(end-start)/3; //freq is 3 GHz
	printf("Time taken is: %llu ns \n",s);
}


