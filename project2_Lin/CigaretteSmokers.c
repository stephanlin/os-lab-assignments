#include <stdio.h>
#include <stdlib.h>

#include "sem.h"
  			
#define PERMS 0666

int lock, agent, smoker_paper, smoker_tobacco, smoker_match; 


void main()
{
	if((lock=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
		printf("\n can't create mutex semaphore");
  		exit(1);
	}

	if((agent=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
		printf("\n can't create mutex semaphore");
  		exit(1);
	}

	if((smoker_paper=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
		printf("\n can't create mutex semaphore");
  		exit(1);
	}

	if((smoker_tobacco=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
		printf("\n can't create mutex semaphore");
  		exit(1);
	}

	if((smoker_match=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
		printf("\n can't create mutex semaphore");
  		exit(1);
	}
	
	sem_create(lock,1);
	sem_create(agent,0);
	sem_create(smoker_paper,0);
	sem_create(smoker_tobacco,0);
	sem_create(smoker_match,0);


	int pid;						// Process ID 
	int i;							// For Loop index
	int status;						// Status of child process for exit
	int N;							// Number of times the agent will update
	int randNum;					// Randnum storage
	
	// Child processes which will do the updates
	if ((pid = fork()) == -1) //Check for a fork error
	{
		perror("Fork failed!");
		exit(1);
	}
	
	if (pid == 0){
	// Supplier Agent
	
		N = 10;
		for(i = 1;i <= N;i++)
		{	
			// Agent
			P(lock);
			randNum = rand() % 3;
			if(randNum == 0)
			{
				printf("Put tobacco and paper on the table\n");
				sleep(1);
				V(smoker_match); // Wake up the smoker with match
			}
			else if(randNum == 1)
			{
				printf("Put tobacco and match on the table\n");
				sleep(1);
				V(smoker_paper); // Wake up the smoker with paper
			}
			else if(randNum == 2)
			{
				printf("Put match and paper on the table\n");
				sleep(1);
				V(smoker_tobacco); // Wake up the smoker with tobacco
			}
			V(lock);
			P(agent); // Agent sleeps
			
		}
	}
	
	else
	{
		// Parent Process
		if ((pid = fork()) == -1) // Check for a fork error
		{
			perror("Fork failed!");
			exit(1);
		}
		if (pid == 0)
		{
			while(1)	// Forever loop
			{
				P(smoker_tobacco); // Sleep right away
				P(lock);
					printf("Smoker#1 with tobacco picks up match and paper\n"); // Already has tobacco
				sleep(1);
				V(agent);
				V(lock);
				printf("Smoker#1 smokes!\n");
			}
		}
		else
		{
		//Parent Process
			if ((pid = fork()) == -1) // Check for a fork error
			{
				perror("Fork failed!");
				exit(1);
			}
			if (pid == 0)
			{
				while(1)	// Forever loop
				{
					P(smoker_paper); // Sleep right away
					P(lock);
						printf("Smoker#2 with paper picks up match and tobacco\n"); // Already has paper
					sleep(1);
					V(agent);
					V(lock);
					printf("Smoker#2 smokes!\n");
				}
			}
			else
			{ 
				if ((pid = fork()) == -1) // Check for a fork error
				{
					perror("Fork failed!");
					exit(1);
				}
				if (pid == 0)
				{
					while(1)	// Forever loop
					{
						P(smoker_match); // Sleep right away
						P(lock);
							printf("Smoker#3 with matches picks up paper and tobacco\n"); // Already has match
						sleep(1);
						V(agent);
						V(lock);
						printf("Smoker#3 smokes!\n");
					}
				}
				else
				{
					pid = wait(&status);
					printf("Process with pid = %d exited with the status %d. \n", pid, status);
				}
			}
		}
	}
	exit(0); 
}