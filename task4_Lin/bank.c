/*
CSc332 OS Lab
Instructor: Arun Adiththan
Author: Weifan Lin
Task 4 Dad-Son Problem
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "sem.h"


#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0  
#define FALSE      			1
#define PERMS 0666 // Read and Write Permissions

FILE *fp1, *fp2, *fp3, *fp4;			/* File Pointers */

int mutex; // Semaphore Mutex

main()
{
	if((mutex=semget(IPC_PRIVATE, 1 ,PERMS | IPC_CREAT)) == -1)
	{
	 printf("Failed to create mutex\n");
  	 exit(1);
	}
	
	// Initialize the semaphore mutex.
	sem_create(mutex,1);

	int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables
	
	//Initialize the file balance to be $100
	fp1 = fopen("balance","w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);
	
	//Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 10;
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);
	
	//Create child processes that will do the updates
	if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	if (pid == CHILD){
	//First Child Process. Dear old dad tries to do some updates.
	
		N=5;
		for(i=1;i<=N; i++)
		{	
			P(mutex);//  The account balance is being accessed, so a mutex here is placed to prevent overwriting.

			printf("Dear old dad is trying to do update.\n");
			fp1 = fopen("balance", "r+");
			fscanf(fp1, "%d", &bal2);
			printf("Dear old dad reads balance = %d \n", bal2);
			
			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand()%15);
			fseek(fp1,0L,0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);

			printf("Dear old dad is done doing update. \n");
			sleep(rand()%5);	/*Go have coffee for 0-4 sec. */

			V(mutex); // The Dad has finished doing updates, allow other process to access the balance.
		}
	}
	
	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{	
				P(mutex); // Need a semaphore here because first son is attemping to access.

				fp3 = fopen("attempt" , "r+");
				fscanf(fp3, "%d", &N_Att);
				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					fscanf(fp2,"%d", &bal2);
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{
						fclose(fp2);
						fclose(fp3);
					}
					else
					{
						sleep(rand()%5);
						fseek(fp2,0L, 0);
						bal2 -=20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
				}
				V(mutex); // First son has finished, allow other processes.
			}
		}
		else
		{
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{
				printf("Second Son's Pid: %d\n",getpid());
				//Third child process. Second poor student tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{	
					P(mutex); // Second son attempting to access, thus we have a semaphore.

					fp3 = fopen("attempt" , "r+");
					fscanf(fp3, "%d", &N_Att);
				
					if(N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}
					else
					{
						printf("Poor SON_2 wants to withdraw money.\n");
						fp2 = fopen("balance", "r+");
						fscanf(fp2,"%d", &bal2);
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{
							fclose(fp2);
							fclose(fp3);
						}
						else
						{
							sleep(rand()%5);
							fseek(fp2,0L, 0);
							bal2 -=20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3,0L, 0);
							N_Att -=1;

							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					}
					V(mutex); //Second son has finished doing updates.
				}
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			}
			exit(0);
		}
		exit(0);
	}
	exit(0);
}