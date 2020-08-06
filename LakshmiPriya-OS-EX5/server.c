#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<errno.h>
#include<unistd.h>

#define BUF_SIZE 20
#define SHM_KEY 12345

struct shmseg 
{
	int cnt;
	int complete;
	char buf[BUF_SIZE];
};

FILE *fptr;

int fill_buffer(char *bufptr, int size) 
{
	int filled_count;
/*
	memset(bufptr, ch, size - 1);
	bufptr[size-1] = '\0';	  
*/

        fscanf(fptr, " %[^\n]", bufptr);

	filled_count = strlen(bufptr);

	return filled_count;
}

int main(int argc, char *argv[]) 
{
	char *file;
	printf("\nEnter file name: ");
	scanf(" %s", file);
	if ((fptr = fopen(file, "r")) == NULL) 
	{
		printf("Error! opening file");
		exit(1);
	}

	int shmid, numtimes;
	struct shmseg *shmptr;
	char *bufptr;
	int spaceavailable;

	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);

	if (shmid == -1) 
	{
		perror("Shared memory");
		return 1;
	}

	shmptr = shmat(shmid, NULL, 0);

	if (shmptr == (void *) -1) 
	{
		perror("Shared memory attach");
		return 1;
	}

	/* Transfer blocks of data from buffer to shared memory */
	bufptr = shmptr->buf;
	spaceavailable = BUF_SIZE;

	do
	{
		shmptr->cnt = fill_buffer(bufptr, spaceavailable);
		shmptr->complete = 0;
		printf("Writing Process: Shared Memory Write: Wrote %d bytes\n", shmptr->cnt);
		bufptr = shmptr->buf;
		spaceavailable = BUF_SIZE;
		numtimes++;
		sleep(3);
	}while(feof(fptr)==0);

	printf("Writing Process: Wrote %d times\n", numtimes);
	shmptr->complete = 1;

	if (shmdt(shmptr) == -1) 
	{
		perror("shmdt");
		return 1;
	}

	if (shmctl(shmid, IPC_RMID, 0) == -1) 
	{
		perror("shmctl");
		return 1;
	}
	printf("Writing Process: Complete\n");

	fclose(fptr);
	return 0;
}



