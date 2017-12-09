#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int fd = open(argv[1], O_WRONLY);

	if (fork())
	{
		// Parent process
		char* string = "From Parent Process\n";
		// wait();
		write(fd, string, strlen(string));

	} else {
		// Child process
		char* string = "From Child Process\n";
		write(fd, string, strlen(string));
	}

	close(fd);
}