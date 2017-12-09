#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd[2];
	pipe(fd);
	char buf[6];
	if(!fork())
	{
		close(fd[0]);
		write(fd[1],"Hello ",6);
		
	}
	else
	{
		close(fd[1]);
		read(fd[0],&buf,sizeof(buf));
		printf("%s\n",buf);
	}
}
