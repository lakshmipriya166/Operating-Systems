#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <dirent.h>
#include <sys/wait.h>
#include <errno.h> 
#include <string.h>

extern int errno; 

int main()
{
	printf("\n\ngetpid():\n");
        printf("\nProcess id of calling process: %d", getpid());

	printf("\n\ngetppid():\n");
        printf("\nProcess id of parent of calling process: %d", getppid()); 
    	
 
printf("#$%$#%");

	printf("\n\nopendir() and readdir():\n");

	struct dirent *de;   
    	DIR *dr = opendir("."); 
  
    	if (dr == NULL)
    	{ 
        	printf("\nCould not open current directory\n" ); 
        	return 0; 
    	} 
  
	while ((de = readdir(dr)) != NULL) 
	        printf("%s\n", de->d_name); 
        closedir(dr);   
  
	printf("\n\nread() and creat():\n");
	int fd=creat("file1.txt", 0766);
	int sz=write(fd, "Hello\n", strlen("Hello\n"));
	if (fd < 0) 
	{ 
		perror("r1"); 
		exit(1); 
	} 
	  
	char *c = (char *) calloc(100, sizeof(char)); ;
	sz = read(fd, c, 10); 
	printf("\nCalled read(%d, c, 10).\nReturned that %d bytes  were read.\n", fd, sz); 
	c[sz] = '\0'; 
	printf("\nThose bytes are as follows: %s\n", c); 


	printf("\n\nopen(), write(), close() and exit():\n"); 
	fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	if (fd < 0) 
	{ 
		perror("r1"); 
	        exit(1); 
	} 
	  
	sz = write(fd, "Hello\n", strlen("Hello\n")); 
	  
	printf("\nCalled write(%d, \"Hello\\n\", %ld)\nReturned %d\n", fd, strlen("Hello\n"), sz); 
	  
	close(fd); 


	printf("\n\nwait():\n");
	if (fork()== 0) 
        printf("\nHC: hello from child"); 
        else
        { 
		printf("\nHP: hello from parent"); 
		wait(NULL); 
		printf("\nCT: child has terminated"); 
        } 
  
        printf("\nBye"); 

	printf("\n\nsleep():\n");
	printf("\nThis is the message before sleep() function");
 	sleep(5);
 	printf("\nThis is the message after 5 second");

	printf("\n\nexecl():\n");
	char *binaryPath = "/bin/ls";
	char *arg1 = "-lh";
	char *arg2 = "/home";
	execl(binaryPath, binaryPath, arg1, arg2, NULL);



}


