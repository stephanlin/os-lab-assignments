/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 3, part 3: Step 1. Create two files namely, destination1.txt and 
	destination2.txt with read, write, and execute permissions.
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
	int fd1, fd2;
	errno = 0;
	fd1 = open("destination1.txt", O_CREAT | O_RDWR, S_IRWXU);	// Opens and creates "destination1.txt" with read-write permissions,
													
	if (fd1 == -1) {
		printf("open() failed with error [%s]\n", strerror(errno));
	}
	else {
		printf("Destination 1: Open() Successful\n");
	}
	close(fd1);

	
	fd2 = open("destination2.txt", O_CREAT | O_RDWR, S_IRWXU); // Opens and creates "destination2.txt" with read-write permissions.

	if (fd2 == -1) {
		printf("\n open() failed with error [%s]\n", strerror(errno));
	}
	else {
		printf("Destination 2: Open() Successful\n");
	}

	close(fd2);



return 0;
}