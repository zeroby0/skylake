//
// Created by Aravind Reddy V on 17/11/17.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// print the number of directories in a folder


int numberofDirectories() {

    pid_t ls_pid, grep_pid, wc_pid;

    int pipefd[2], pipefd2[2];

    pipe(pipefd); // read, write
    pipe(pipefd2);

    if((ls_pid = fork()) == 0) { // ls child process

        close(pipefd[0]);
        close(pipefd2[0]); close(pipefd2[1]);

        close(STDOUT_FILENO); dup(pipefd[1]);
        // Now, whatever gets written to stdout is written to the write end of pipe

        execl("/bin/ls", "ls", "-l", NULL);
        perror("exec ls failed");
        exit(EXIT_FAILURE);
    }

    if((grep_pid = fork()) == 0) { // ls child process

        close(pipefd[1]);
        close(pipefd2[0]);

        close(STDIN_FILENO); dup(pipefd[0]);
        close(STDOUT_FILENO); dup(pipefd2[1]);
        // Now, whatever gets written to stdout is written to the write end of pipe
        // and stdin is the read end

        // /usr/bin/grep in MacOS
        execl("/bin/grep", "grep", "^d", NULL);
        perror("exec grep failed");
        exit(EXIT_FAILURE);
    }


    if((wc_pid = fork()) == 0) {

        close(pipefd[0]); close(pipefd[1]);
        close(pipefd2[1]);

        close(STDIN_FILENO); dup(pipefd2[0]);
        // Now, whatever is written to pipe is written to STDIN

        execl("/usr/bin/wc", "wc", "-l", NULL);
        perror("exec wc failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int main() {
    numberofDirectories();
}
