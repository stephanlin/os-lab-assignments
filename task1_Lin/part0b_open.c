/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 1, part 0(b): Write a C program where open system call creates a new file 
  (say, destination.txt) and then opens it. (Hint: use the bitwise OR flag)
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    errno = 0;
    // open argument file; create new if does not exit with read-write permission
    fd = open(argv[1], O_CREAT | O_RDWR, S_IRWXU);  

    if (fd == -1) {
        printf("\n open() failed with error [%s]\n", strerror(errno));
    }
    else {
        printf("\n Open() Successful\n");
    }
    
    close(fd);

return 0;
}