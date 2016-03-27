/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Project 1, part 2: Average Grade Calculator
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{ 
    int x, y; // x - number of chapters y - number of homeworks 
    double average = 0; 
    int row_count = 0, col_count = 0, manager_count = 0, worker_count = 0, status;
    printf("Enter the number of Chapters: "); 
    scanf("%d", &x);
    printf("Enter the number of Homeworks per chapter: "); 
    scanf("%d", &y);
    const int NUM_ROWS = 10;
    const int NUM_COLLUMNS = x*y;

    double grades [NUM_COLLUMNS] [NUM_ROWS]; // 2D Array to store grades of homeworks
    double averages [NUM_COLLUMNS]; // array to store homework averages

    FILE * source = fopen("source.txt", "r"); // open file with read permissions

    while(row_count < NUM_ROWS) // store 2D array values from source file
    {
        while(col_count < NUM_COLLUMNS)
        {
            fscanf(source, "%lf", &grades[col_count][row_count]);
            col_count++;
        }
            col_count =0;
            row_count++;
    }

    row_count = 0;
    col_count = 0;
    while(manager_count < x) // a manager for each chapter
    {
        wait(&status);
        pid_t manager_pid = fork();
        if(manager_pid == 0)
        {
            col_count = y * manager_count; // calculate start of next chapter in table
            while(worker_count < y) // a worker for each homework
            { 
                wait(&status);
                pid_t worker_pid= fork();
                if(worker_pid == 0)
                {
                    while(row_count < NUM_ROWS)
                    { 
                        average += grades[col_count][row_count]; // add up grades in the collumn
                        row_count++;    
                    }
                    averages[col_count] = average / NUM_ROWS; // compute and store the average
                    printf("Average of Homework#%d: %f \n",(col_count + 1), averages[col_count]); // print HW# and Average
                    exit(0); 
                }
                else if (worker_pid < 0)  // check for error
                {
                    perror("Fork Error");
                }
                else
                {
                    if(wait(&status) == -1) // wait for child to terminate
                    {
                        printf("Error\n");
                    }
                }
                    row_count = 0; // reinitialize count
                    col_count++; 
                    worker_count++;
            }
                exit(0);
        }
        else if(manager_pid < 0) // check for error
        {
            perror("Fork Error");
            return 1;
        }
        else
        {
            if(wait(&status) == -1) //wait for child to terminate
            {
                printf("Error\n");
            }
        }
            worker_count = 0;
            manager_count++;
        }
        
    fclose(source); 

    return 0;
}
