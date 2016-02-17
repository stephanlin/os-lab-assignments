/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 1, part 1: Write a C program to implement a command called displaycontent 
	that takes a (text) file name as argument and display its contents. 
	Report an appropriate message if the file does not exist or can’t be opened
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	int fd; int rd; int ct;
	errno = 0;

	
	fd = open(argv[1], O_RDWR);	// open argument file for read-writing

	if (fd == -1)
	{
		printf("\n Error: [%s]\n", strerror(errno));
	}
	else {
		char buf[BUFSIZ]; // Declare an array of char called buf that has a size of BUFSIZ (a macro constant)

	
		while ( (rd = read(fd, buf, BUFSIZ)) > 0) {			// rd is assigned the return value of read, which is the number of characters that are read from fd
			write(1, buf, rd);								// write to the terminal whatever the 'read' syscall reads from the file
		}
	}
	close(fd);

	return 0;

}