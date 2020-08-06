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

int main(int argc, char *argv[]) 
{
	int shmid;
	struct shmseg *shmptr;

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

	while (shmptr->complete != 1) 
	{
		printf("Segment contains : \n\"%s\"\n", shmptr->buf);
		if (shmptr->cnt == -1) 
		{
			perror("read");
			return 1;
		}
		printf("Reading Process: Shared Memory: Read %d bytes\n", shmptr->cnt);
		sleep(3);
	}

	printf("Reading Process: Reading Done, Detaching Shared Memory\n");
	if (shmdt(shmptr) == -1) 
	{
		perror("shmdt");
		return 1;
	}
	printf("Reading Process: Complete\n");

	return 0;
}
