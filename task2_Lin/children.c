/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 2, part 1: Write a program children.c, and let the parent process 
	produce two child processes. One prints out "I am child one, 
	my pid is: " PID, and the other prints out "I am child two, 
	my pid is: " PID. Guarantee that the parent terminates after 
	the children terminate
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{	
	int status, pid_1, pid_2;
	pid_1 = fork();   // Create the first child
	wait(&status);
	
	if(pid_1 != 0){
		printf("I am the parent, my PID is: %d\n", getpid()); 
	}

	else{
		printf("I am child one, my PID is: %d\n", getpid());  
		pid_2 = fork(); // Create the second child
		wait(&status);

		if (pid_2 == 0){	
		printf("I am child two, my PID is: %d\n", getpid());
		}
	}
	
	return 0;
}