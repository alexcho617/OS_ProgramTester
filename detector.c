//21800691 Sungjin Cho Operating Systems Homework 2
//detector.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("-----Detector Initiated------\n");
    FILE *f1 = fopen("targetresult.txt", "r");
    FILE *f2 = fopen("solutionresult.txt", "r");

    if (f1 == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }
        if (f2 == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }
    char str1[128];
    char str2[128];

    while (fgets(str1, sizeof(str1), f1) != NULL)
    {
        while(fgets(str2, sizeof(str2), f2) != NULL)
        {
            if (strcmp(str1,str2)==0)
            {
                printf("Test Success\n");
            }
            else
            {
                printf("Test Fail\n");

            }
        } 
    }
    fclose(f1);
    fclose(f2);
}