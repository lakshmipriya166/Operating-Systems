#include <stdio.h> 
#include <unistd.h> 
#define   MAX_COUNT  200 

extern int errno; 

void  ChildProcess(void);                /* child process prototype  */ 
void  ParentProcess(void);               /* parent process prototype */ 

int  main(void) 
{
	printf("fork():\n");
	pid_t  pid;
	pid = fork();
	if (pid == 0)
		ChildProcess();
	else
		ParentProcess(); 


} 

void  ChildProcess(void) 
{
	int   i;
	for (i = 1; i <= MAX_COUNT; i++)
	   printf("   This line is from child, value = %d\n", i);
	printf("   *** Child process is done ***\n"); 
} 

void  ParentProcess(void) 
{
	int   i;
	for (i = 1; i <= MAX_COUNT; i++)
	   printf("This line is from parent, value = %d\n", i);
	printf("*** Parent is done ***\n"); 
}
