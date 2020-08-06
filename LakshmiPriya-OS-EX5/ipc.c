# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
#include <sys/prctl.h>

// parent writing a char in shared memory and child reads it and prints it.

int main()
{
	int pid;
	char *a,*b,c;
	int id,n,i;

	// you can create a shared memory between parent and child here or you can 
	//create inside them separately.




	while(1)
	{
		id=shmget(111, 50, IPC_CREAT | 00666);
		pid=fork();

		if(pid>0) //parent
		{
			// id=shmget(111,50,IPC_CREAT | 00666);
			a=shmat(id, NULL, 0);
			printf("\nEnter data or 0 to exit: ");
			scanf(" %[^\n]", a);

			if(strcmp(a, "0")==0 || strcmp(a, "")==0)
			{
				kill(0, SIGINT);  // send an INT signal
				kill(0, SIGKILL); // paranoid: if a child catch INT it will get a KILL
			}
			wait(NULL);
			shmdt(a);
		}
		else //child
		{
			sleep(3);
			//id=shmget(111,50,0);
			b=shmat(id,NULL,0);

			printf("\n Child: ");

			int i=0;
			while(b[i]!='\0') 
			{
				printf("%c",toupper(b[i])); 
				i++;
			}
			printf("\n");

			shmdt(b);
		}
		shmctl(id, IPC_RMID,NULL);
	}
}
