/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 1, part 2: Write a C program that mimics the cp command using open() 
	system call to open source.txt file in read-only mode and copy the 
	contents of it to destination.txt using read() and write() system calls
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	int fd; int rd; int acs;
	int dest;

	errno = 0;

	fd = open(argv[1], O_RDONLY);

	// Check if the file that we are copying to already exists
	//If so, unlink (delete) it
	acs = access(argv[2], F_OK); 
	if (acs == 0)
	{
		unlink(argv[2]);
	}

	dest = open(argv[2], O_CREAT | O_RDWR, S_IRWXU); // Open file and assign it to dest. If it does not exist, create it with read-write access

	if (fd == -1)
	{
		printf("\n Error: [%s]\n", strerror(errno));
	}
	else {
		char buf[BUFSIZ];
	
		while (( rd = read(fd, buf, BUFSIZ)) > 0) {  // While the number of characters read are greater than 0, write it into dest (second argument)
			write(dest, buf, rd);
		}
	}
	close(fd);
	close(dest);

	return 0;

}