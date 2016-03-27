/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Project 1, part 1: Write a special simple command interpreter that takes a 
	command and its arguments. This inter- preter is a program where the main 
	process creates a child process to execute the command using exec() family 
	functions. After executing the command, it asks for a new command input 
	(i.e., parent wait for child). The interpreter program will get terminated 
	when the user enters quit.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main (int argc, char* argv[]) {
	int status, pid;
	char c[64];
	char *token;
	char *arr[20] = {NULL};

	printf ("Please enter command lines: \n");
	scanf(" %[^\n]s", c);

	while (strcmp(c,"quit")) { // terminated when enters quit

		token = strtok(c," ");
		int i = 0;
		while(token != NULL) {
	     arr[i]= token;  // array where arguements are stored
	     token = strtok(NULL," ");
	     i++;
	   	}
		
		pid = fork();  // fork a child process to execute the command line
		wait(&status);
		if (pid == 0) {
	  	execvp (arr[0],arr);
	  	printf ("EXECVP Failed\n");
		}

		int j;
		for (j=0; j < i; ++j)
			arr[j] = NULL; // clear the array
		i = 0;
		printf ("Please enter command lines: \n");
		scanf(" %[^\n]s", c);
	}
	return 0;
}