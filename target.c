//21800691 Sungjin Cho Operating Systems Homework 2
//target.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() 
{
    char stringfromparent[256];
    scanf("%s", stringfromparent); //stdin
    int stringlength = strlen(stringfromparent);
   
    FILE *fp;
    fp = fopen("targetresult.txt", "a");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp,"%d\n",stringlength);
    fclose(fp);
    return 0;
}