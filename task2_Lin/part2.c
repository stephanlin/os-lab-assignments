/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 2, part 2: Consider the parent process as P. The program consists of 
	fork() system call statements placed at different points in the code 
	to create new processes Q and R. The program also shows three variables: 
	a, b, and pid - with the print out of these variables occurring from 
	various processes. Show the values of pid, a, and b printed by the 
	processes P, Q, and R.
*/


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{
	int a = 10, b = 25, fq=0, fr=0;
	fq = fork(); // fork a child - call it process Q
	if(fq == 0){		// Child successfully forked
		a = a+b;
		printf("Process Q - Value of a: %d, Value of b: %d, Value of pid: %d\n", a, b, getpid());
		fr = fork(); // fork another child - call it process R
		if (fr != 0){
			b = b+20;
			printf("Process Q - Value of a: %d, Value of b: %d, Value of pid: %d\n", a, b, getpid());
		}
		else{
			a=(a*b)+30;
			printf("Process R - Value of a: %d, Value of b: %d, Value of pid: %d\n", a, b, getpid());
		}
	}
	else{
		b=a+b-5;
		printf("Process P - Value of a: %d, Value of b: %d, value of pid: %d\n", a, b, getpid());
	}

	return 0;
}
