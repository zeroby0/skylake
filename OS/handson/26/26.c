#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
	// execl("./exe", NULL);
	// cannot run both in one file. execl replaces
	execl("./exe", NULL, "1", "2", NULL);
}