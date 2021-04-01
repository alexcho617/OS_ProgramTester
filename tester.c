//21800691 Sungjin Cho Operating Systems Homework 2
//tester.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <string.h>
#include <dirent.h>
#define READ 0
#define WRITE 1
#define ROW 5
#define COLUMN 10

int pipes[2];
char filecontents[COLUMN];
char filecontents_arr[ROW][COLUMN];
void parent_proc_target()
{
    close(pipes[WRITE]);
    dup2(pipes[READ], 0);
    //printf("1\n");
    execl("./target", "target", NULL);
}
void parent_proc_solution()
{
    close(pipes[WRITE]);
    dup2(pipes[READ], 0);
    //printf("1\n");
    execl("./solution", "solution", NULL);
}

void child_proc()
{
    char buf[256] = {0};
    close(pipes[READ]);
    sprintf(buf, "%s", filecontents); //buf에 1저장
    //printf("child_proc_target:%s\n", buf);
    write(pipes[WRITE], buf, 256);
    sleep(1);
    close(pipes[WRITE]);
}

int main(int argc, char *argv[])
{
    pid_t target_pid, solution_pid;
    char *test_dir, *target_file, *solution_file; //solution/target/testcase directory
    test_dir = argv[1];
    target_file = argv[2];
    solution_file = argv[3];
    char header[10] = "/,";

    strcat(header, target_file); // add the ./ infront of executables
    strcat(header, solution_file);

    //read value from text files
    DIR *folder;
    struct dirent *entry;
    folder = opendir(test_dir); //absolute directory given to opendir

    if (folder == NULL) //file fail check
    {
        perror("Unable to read directory\n");
        exit(1);
    }

    char currentdir[2] = ".";
    char parentdir[3] = "..";

    int arrindex = 0;
    while ((entry = readdir(folder)))
    { //filter current and parent directories
        char filetoread[200] = "";
        if (strcmp(entry->d_name, currentdir) != 0 && strcmp(entry->d_name, parentdir) != 0)
        {
            strcat(filetoread, test_dir);
            strcat(filetoread, "/");
            strcat(filetoread, entry->d_name);
            //printf("%s\n", filetoread);

            FILE *fp; //read the file
            fp = fopen(filetoread, "r");

            if (fp == NULL) //file fail check
            {
                perror("Unable to open file\n");
                exit(1);
            }
            fscanf(fp, "%s", filecontents);                   //saved at filecontents[10]
            strcpy(filecontents_arr[arrindex], filecontents); //saved at filecontents_arr[arrindex]
            arrindex++;

            fclose;
        }             //filter for directory
    }                 //readdir
    closedir(folder); //folder contents exhausted

    //target loop
    printf("Working Target...\n");
    for (int i = 0; i < ROW; i++)
    {
        pipe(pipes);
        if (pipe(pipes) != 0) //pipe failecheck
        {
            perror("Error");
            exit(1);
        }
        target_pid = fork(); //target stuff
        if (target_pid == 0)
        {
            strcpy(filecontents,filecontents_arr[i]);
            child_proc(); //open pipe buffer contents
        }
        else
        {
            wait(0x0);
            parent_proc_target(); //run target
        }
    }
    //solution loop
    printf("Working Solution...\n");
    for (int i = 0; i < ROW; i++)
    {
        pipe(pipes);
        if (pipe(pipes) != 0) //pipe failecheck
        {
            perror("Error");
            exit(1);
        }

        solution_pid = fork(); //solution stuff
        if (solution_pid == 0)
        {
            strcpy(filecontents,filecontents_arr[i]);
            child_proc(); //open pipe buffer contents
        }
        else
        {
            wait(0x0);
            parent_proc_solution(); //run solutino
        }
    }
    wait(0);
    printf("Result Created: \"targetresult.txt\", \"solutionresult.txt\"\n");
}



