/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 3, part 1: Write a program where a child is created to execute command 
	that tells you the date and time in Unix. Use execl(...). Note, you need 
	to specify the full path of the file name that gives you date and time 
	information. Announce the successful forking of child process by displaying 
	its PID.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{	
	int status, pid_1;
	pid_1 = fork();   // Create the first child
	wait(&status);
	if(pid_1 != 0){
		printf("I am the parent, my PID is: %d\n", getpid());    // Parent prints out this line
	}

	else{
		printf("I am child one, my PID is: %d\n", getpid());   // If pid_1 is 0, child one prints this line and another child is created.
		execl("/bin/date", "date", NULL);  // Prints out date and time in first child.
		printf("EXECL Failed\n");
		
	}
	return 0;
}