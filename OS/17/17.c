//
// Created by Aravind Reddy V on 17/11/17.
//

// Execute ls -al | wc with
// dup
// dup2
// fcntl

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int withdup2() {
    int pipefd[2];
    pid_t ls_pid, wc_pid;

    pipe(pipefd); // read, write

    if((ls_pid = fork()) == 0) { // ls child process

        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        // Now, whatever gets written to stdout is written to write end of pipe

        execl("/bin/ls", "ls", "-l", NULL);
        perror("exec ls failed");
        exit(EXIT_FAILURE);
    }

    if((wc_pid = fork()) == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        // Now, whatever is written to pipe is written to STDIN

        execl("/usr/bin/wc", "wc", NULL);
        perror("exec wc failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int withdup() {
    int pipefd[2];
    pid_t ls_pid, wc_pid;

    pipe(pipefd); // read, write

    if((ls_pid = fork()) == 0) {
        close(pipefd[0]);
        close(STDOUT_FILENO);
        dup(pipefd[1]); // as stdout is empty, fd = 1 now points at the write end of the pipe
        close(pipefd[1]);
        // STDOUT is now redirected to write end of the pipe
        execl("/bin/ls", "ls", "-l", NULL);
        perror("exec ls failed");
        exit(EXIT_FAILURE);
    }

    if((wc_pid = fork()) == 0 ) {
        close(pipefd[1]);
        close(STDIN_FILENO);
        dup(pipefd[0]);
        close(pipefd[0]);
        // read end of pipe is now redirected to STDIN
        execl("/usr/bin/wc", "wc", NULL);
        perror("exec wc failed");
        exit(EXIT_FAILURE);
    }

    return  EXIT_SUCCESS;
}

int withfcntl() {
    int pipefd[2];
    pid_t ls_pid, wc_pid;

    pipe(pipefd); // read, write

    if((ls_pid = fork()) == 0) {
        close(pipefd[0]);
        close(STDOUT_FILENO);
        fcntl(pipefd[1], F_DUPFD); // as stdout is empty, fd = 1 now points at the write end of the pipe
        close(pipefd[1]);
        // STDOUT is now redirected to write end of the pipe
        execl("/bin/ls", "ls", "-al", NULL);
        perror("exec ls failed");
        exit(EXIT_FAILURE);
    }

    if((wc_pid = fork()) == 0 ) {
        close(pipefd[1]);
        close(STDIN_FILENO);
        fcntl(pipefd[0], F_DUPFD);
        close(pipefd[0]);
        // read end of pipe is now redirected to STDIN
        execl("/usr/bin/wc", "wc", NULL);
        perror("exec wc failed");
        exit(EXIT_FAILURE);
    }

    return  EXIT_SUCCESS;
}

int main() {
   return withfcntl();
}

