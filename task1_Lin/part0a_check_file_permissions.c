/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 1, part 0(a): Extend code snippet 1 to check for read and write access 
  permissions of a given file
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
int main (int argc, char* argv[])
{
    char* filepath = argv[1];
    int returnval;
    
    // Check file existence
    returnval = access (filepath, F_OK);
    if (returnval == 0)
       printf ("\n%s exists\n", filepath);
    else
    {
       if (errno == ENOENT)
           printf ("%s does not exist\n", filepath);
       else if (errno == EACCES)
           printf ("%s is not accessible\n", filepath);
       return 0;
    }

    // Check read access
    returnval = access (filepath, R_OK);
    if (returnval == 0)
      printf ("%s is readable\n", filepath);
    else
      printf ("%s is not readable (access denied)\n", filepath);

    // Check write access
    returnval = access (filepath, W_OK);
    if (returnval == 0)
      printf ("%s is writable\n", filepath);
    else if (errno == EACCES)
      printf ("%s is not writable (access denied)\n", filepath);
    else if (errno == EROFS)
      printf ("%s is not writable (read-only filesystem)\n", filepath);

    return 0;
}
