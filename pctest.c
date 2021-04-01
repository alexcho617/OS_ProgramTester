//21800691 Sungjin Cho Operating Systems Homework 1
//pctest.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#define READ 0
#define WRITE 1

void handler(int sig)
{
    if(sig == SIGALRM)
    {
        printf("timeout\n");
        exit(0);
    }
    
}

int main(int argc, char* argv[]) 
{
    //variable declaration
    pid_t compiler, tester, detector; //process variables
    int timeout = 0, index, opt; //getopt variables
    extern char *optarg;
    extern int optind;
    char *test_dir, *target_file, *solution_file; //solution/target/testcase directory
    
    struct itimerval timer; //timeout signal handler
    signal(SIGALRM, handler);

    //get optional arguments from command line
    while((opt = getopt(argc,argv, "i:t:")) != -1)
    {
        switch (opt)
        {
        case 'i':
            test_dir = optarg;
            break;
        case 't':
            timeout = atoi(optarg);
            if(timeout < 1 || timeout > 10)
            {
                printf("timeout must be in range of 1~10\n");
                exit(0); 
            }
            break;
        case '?':
            printf("Non-option argument");
            exit(1);
        default:
            printf("error in getopt from default case");
            break;
        }
    }

    //argument match check
    if(argc - optind != 2)
    {
        printf("error in argument match\n");
        exit(1);
    }

    //get file names from argv
    for(int i = optind; i < argc; i++) //repeat as many times as number of argument
    {
        if(i == optind)
        {
            solution_file = argv[i];
        }
        else
        {
            target_file = argv[i];
        }
    }

    //measure timeout and send signal
    timer.it_value.tv_sec = timeout;
    timer.it_interval = timer.it_value;
    setitimer(ITIMER_REAL, &timer, NULL);

    compiler = fork(); //COMPILER
    if (compiler == 0) 
    {
        pid_t compiler_child;
        compiler_child = fork();
        //gcc compiler
        if(compiler_child == 0) 
        {
            //printf("gcc compiler \n");
            execl("/usr/bin/gcc", "gcc", "compiler.c", "-o", "compiler", (char*) NULL);
        }
        //run compiler
        else 
        {
            pid_t term_compiler_child;
            int exit_code_compiler_child;
            term_compiler_child = wait(&exit_code_compiler_child); //grand_target process가 끝날 때 까지 기다림
            
            execl("./compiler", "compiler", target_file, solution_file, (char*) NULL);
        }
    }

    else 
    { //parent
        wait(0x0); // this will wait for the compiler

        tester = fork(); //TESTER
        if (tester == 0) 
        {
            pid_t tester_child;
            tester_child = fork();
            
            if(tester_child == 0) 
            {//gcc tester
                execl("/usr/bin/gcc", "gcc", "tester.c", "-o", "tester", (char*) NULL);
            }//gcc tester
            
            else 
            {//run tester
                pid_t term_tester_child;
                int exit_code_tester_child;
                term_tester_child = wait(&exit_code_tester_child); //grand_target process가 끝날 때 까지 기다림
                execl("./tester", "tester", test_dir, "target", "solution", (char*) NULL);
            }//run tester
        }//TESTER

        else 
        {
            wait(0x0); //this will wait for the tester

            detector = fork(); 
            if (detector == 0) 
            {//DETECTOR
            pid_t detector_child;
            detector_child = fork();
            
            if(detector_child == 0) 
            {//gcc detector
                execl("/usr/bin/gcc", "gcc", "detector.c", "-o", "detector", (char*) NULL);
            }//gcc detector
            
            else 
            {//run detector
                pid_t term_detector_child;
                int exit_code_detector_child;
                term_detector_child = wait(&exit_code_detector_child); //grand_target process가 끝날 때 까지 기다림
                execl("./detector", "detector", (char*) NULL);
            }//run detector
        }//DETECTOR
            else
            {//stuff after all chilld ran and returned
                wait(0x0);
                //printf("\nEND OF  PCTEST PARENT\n");
            }//end of ancestor
        }//parent
    }//parent
}