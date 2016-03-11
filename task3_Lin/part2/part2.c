/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 3, part 2: Write a program where a child is created to execute a command 
	that shows all files (including hid- den files) in a directory with 
	information such as permissions, owner, size, and when last modified.
	Use execvp(...). For the command to list directory contents with various 
	options, refer the handout on Unix file system sent to you in the first class.
	Announce the successful forking of child process by displaying its PID.
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

		char *argv[] = {"ls", "-laxo", NULL};
		execvp(argv[0],argv);
		printf("EXECVP Failed\n");	
		
	}
	
	return 0;
}