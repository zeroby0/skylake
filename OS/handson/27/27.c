#include <unistd.h>
#include <stdio.h>

int main() {
	char* lsPath = "/bin/ls";
	// execl(lsPath, "-l", "-R", "-G", "../", NULL);
	// execlp(lsPath, "-l", "-R", "-G", "../", NULL);
	// execle(lsPath, "-l", "-R", "-G", "../", NULL);

	// char* args[5];
	// args[0] = "ls";
	// args[1] = "-l";
	// args[2] = "-R";
	// args[3] = "../";
	// args[4] = NULL;
	// execv(lsPath, args);

	char* args[5];
	args[0] = "ls";
	args[1] = "-l";
	args[2] = "-R";
	args[3] = "../";
	args[4] = NULL;
	execvp(lsPath, args);





}


// #include <unistd.h>
// #include <sys/time.h>
// #include <stdlib.h>
// #include <stdio.h>
// if(!fork()){

// 	setsid()
// 	chdir('/');
// 	umask(0);
// 	while(1) {
// 		sleep(15);
// 		printf("dmn prcs\n");
// 	}
// }
// else exit;