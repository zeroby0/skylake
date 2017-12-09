#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	if(!fork()){

		setsid();
		chdir("/");
		umask(0);
		while(1) {
			sleep(2);
			printf("dmn prcs\n");
		}
	}
	else {
		exit;
	}
}
