//21800691 Sungjin Cho Operating Systems Homework 2
//compiler.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{   

    pid_t target_pid, solution_pid;
    char *target_file, *solution_file; //solution/target/
    target_file = argv[1];
    solution_file = argv[2];

    target_pid = fork();
    if (target_pid == 0) {
            execl("/usr/bin/gcc", "gcc", target_file, "-o", "target", (char*) NULL);
    }

    else { 
        solution_pid = fork();
        if (solution_pid == 0) {
            execl("/usr/bin/gcc", "gcc", solution_file, "-o", "solution", (char*) NULL);
        }
        else {
        wait(0x0);
        //printf("Compiler Finished\n");
        }
    }
    return 0;
}