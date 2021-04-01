# OShw2

This is one of assignment in from Handong Global Univeristy, Operating Systems class.
Use of this code is not allowed other than the proffessor and TA's

https://www.youtube.com/watch?v=TrLgpDk0O-g&ab_channel=Alexkun  
# Pctest
pctest is a program designed to use multi-process, dup2, pipe to compare solution program and a target program.
pctest.c gets 4 argumeents from commandline.

There are 3 major parts.

## Compiler
Gets two solution and target c files from commnad line and turns them in to executables.

## Tester
Gets two executables(target, solution) from compiler and one directory which contains all the testcase inputs.
It returns a result report for each of the executables.

## Detector
Gets result and compares them. Will return true if both output are same, false otherwise.

## Test Subject
the subjects target.c and solution.c 's aim is to receive a string from it's parent's processor via pipe, and calculate the length of the string.

# What I couldn't implement
Measuring time for each process.
Implementing error signals
