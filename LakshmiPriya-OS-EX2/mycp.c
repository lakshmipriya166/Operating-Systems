#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

void cp(int argc, char *argv[])
{
	int fdsrc, fddest, sz;

	fdsrc=open(argv[1], O_RDONLY);
	
	if(fdsrc==-1)
	{
		printf("\nError Number: %d", errno);
		perror("Program");
		exit(0);
	}
	
	char *c=(char *)calloc(100, sizeof(char));
	sz=read(fdsrc, c, 100);
	c[sz]='\0';
	
	printf("\n\n%s content: \n%s", argv[1], c);
	for(int i=2; i<argc; i++)
	{
		fddest=creat(argv[i], O_APPEND);
		
		if(fddest==-1)
		{
			printf("\nError Number: %d", errno);
			perror("Program");
			exit(0);
		}

		
		write(fddest, c, sz);

		sz=read(fddest, c, sz);
		c[sz]='\0';
		
		printf("\n\n%s content: \n%s", argv[i], c);
		

		if (close(fddest)<0)  
		{ 
			perror("c1"); 
			exit(1); 
		}  
	}
	if(close(fdsrc)<0)
	{
		perror("c2");
		exit(1);
	} 
	printf("\nClosed the files.\n"); 

}

void cp_f(int argc, char *argv[])
{
	cp(argc, argv);
}

void cp_v(int argc, char *argv[])
{
	int fdsrc, fddest, sz;

	fdsrc=open(argv[1], O_RDONLY);
	
	if(fdsrc==-1)
	{
		printf("\nError Number: %d", errno);
		perror("Program");
		exit(0);
	}
	
	char *c=(char *)calloc(100, sizeof(char));
	sz=read(fdsrc, c, 100);
	c[sz]='\0';
	
	printf("\n\n%s content: \n%s", argv[1], c);
	for(int i=2; i<argc; i++)
	{
		printf("\n'%s' -> '%s'", argv[1], argv[i]);
		fddest=creat(argv[i], O_APPEND);
		
		if(fddest==-1)
		{
			printf("\nError Number: %d", errno);
			perror("Program");
			exit(0);
		}

		
		write(fddest, c, sz);

		sz=read(fddest, c, sz);
		c[sz]='\0';
		
		printf("\n\n%s content: \n%s", argv[i], c);
		

		if (close(fddest)<0)  
		{ 
			perror("c1"); 
			exit(1); 
		}  
	}
	if(close(fdsrc)<0)
	{
		perror("c2");
		exit(1);
	} 
	printf("\nClosed the files.\n"); 

}

void cp_i(int argc, char *argv[])
{
	int fdsrc, fddest, sz, choice=0;

	fdsrc=open(argv[1], O_RDONLY);
	
	if(fdsrc==-1)
	{
		printf("\nError Number: %d", errno);
		perror("Program");
		exit(0);
	}
	
	char *c=(char *)calloc(100, sizeof(char));
	sz=read(fdsrc, c, 100);
	c[sz]='\0';
	
	printf("\n\n%s content: \n%s", argv[1], c);

	for(int i=2; i<argc; i++)
	{
		fddest=open(argv[i], O_RDONLY);
	
		if(fddest!=-1)
		{
			printf("\nOverwrite existing file %s(1-yes;0-no) 0/1? : ", argv[i]);
			scanf("%d", &choice);
			if(choice==0)
				continue;
		}
	
		fddest=creat(argv[i], O_APPEND);
		
		if(fddest==-1)
		{
			printf("\nError Number: %d", errno);
			perror("Program");
			exit(0);
		}

		
		write(fddest, c, sz);

		sz=read(fddest, c, sz);
		c[sz]='\0';
		
		printf("\n\n%s content: \n%s", argv[i], c);
		

		if (close(fddest)<0)  
		{ 
			perror("c1"); 
			exit(1); 
		}  
	}

	if(close(fdsrc)<0)
	{
		perror("c2");
		exit(1);
	} 
	printf("\nClosed the files.\n"); 

}

int main(int argc, char *argv[])
{
	printf("\n\nUsing cp:\n");
	cp(argc, argv);
	printf("\n\nUsing cp -i:\n");
	cp_i(argc, argv);
	printf("\n\nUsing cp -v:\n");	
	cp_v(argc, argv);
	printf("\n\nUsing cp -f:\n");	
	cp_f(argc, argv);

	

	return 0;
}
