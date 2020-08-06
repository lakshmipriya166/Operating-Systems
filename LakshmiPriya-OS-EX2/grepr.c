#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

int fileopen(char *file)
{
	int fdsrc;

	fdsrc=open(file, O_RDONLY);
	
	if(fdsrc==-1)
	{
		printf("\nError Number: %d", errno);
		perror("Program");
		exit(0);
	}

	return fdsrc;
}

void fileclose(int fdsrc)
{
	if (close(fdsrc)<0)  
	{ 
		perror("c1"); 
		exit(1); 
	}  
	printf("\n\nClosed the file.\n");
}

void grep(char *file, char *expr)
{
	int sz, i=0, j=0;
	int fdsrc=fileopen(file);

	char *c=(char *)calloc(100, sizeof(char));
	char *line=(char *)calloc(100, sizeof(char));

	sz=read(fdsrc, c, 100);
	c[sz]='\0';

	while(i<sz)
	{
		j=0;
		while(c[i]!='\n')
		{
			line[j]=c[i];
			i++;
			j++;
		}
		line[j]='\0';
		if(strstr(line, expr)!=0)
			printf("\n%s", line);

		i++;
		
	}
	
	fileclose(fdsrc);
	free(c);
	free(line);
}

void grep_v(char *file, char *expr)
{
	int sz, i=0, j=0;
	int fdsrc=fileopen(file);

	char *c=(char *)calloc(100, sizeof(char));
	char *line=(char *)calloc(100, sizeof(char));

	sz=read(fdsrc, c, 100);
	c[sz]='\0';

	while(i<sz)
	{
		j=0;
		while(c[i]!='\n')
		{
			line[j]=c[i];
			i++;
			j++;
		}
		line[j]='\0';
		if(strstr(line, expr)==0)
			printf("\n%s", line);

		i++;
		
	}
	
	fileclose(fdsrc);
	free(c);
	free(line);
}

void grep_c(char *file, char *expr)
{
	int sz, i=0, j=0, count=0;
	int fdsrc=fileopen(file);

	char *c=(char *)calloc(100, sizeof(char));
	char *line=(char *)calloc(100, sizeof(char));

	sz=read(fdsrc, c, 100);
	c[sz]='\0';

	while(i<sz)
	{
		j=0;
		while(c[i]!='\n')
		{
			line[j]=c[i];
			i++;
			j++;
		}
		line[j]='\0';
		if(strstr(line, expr)!=0)
			count++;
		i++;
		
	}
	
	printf("%d", count);

	fileclose(fdsrc);
	free(c);
	free(line);
}

void grep_n(char *file, char *expr)
{
	int sz, i=0, j=0, linecount=1;
	int fdsrc=fileopen(file);

	char *c=(char *)calloc(100, sizeof(char));
	char *line=(char *)calloc(100, sizeof(char));

	sz=read(fdsrc, c, 100);
	c[sz]='\0';

	while(i<sz)
	{
		j=0;
		while(c[i]!='\n')
		{
			line[j]=c[i];
			i++;
			j++;
		}
		line[j]='\0';
		if(strstr(line, expr)!=0)
			printf("\n%d:%s", linecount, line);

		i++;
		linecount++;
	}
	
	fileclose(fdsrc);
	free(c);
	free(line);
}

void grep_l(char *file, char *expr)
{
	int sz, i=0, j=0;
	int fdsrc=fileopen(file);

	char *c=(char *)calloc(100, sizeof(char));
	char *line=(char *)calloc(100, sizeof(char));

	sz=read(fdsrc, c, 100);
	c[sz]='\0';

	while(i<sz)
	{
		j=0;
		while(c[i]!='\n')
		{
			line[j]=c[i];
			i++;
			j++;
		}
		line[j]='\0';
		if(strstr(line, expr)!=0)
		{
			printf("%s", file);
			fileclose(fdsrc);
			return;
		}
		i++;
		
	}
	
	fileclose(fdsrc);
	free(c);
	free(line);
}

int main(int argc, char *argv[])
{

	printf("\nResult of grep %s in file %s: ", argv[1], argv[2]);
	grep(argv[2], argv[1]);

	printf("\nResult of grep -v %s in file %s: ", argv[1], argv[2]);
	grep_v(argv[2], argv[1]);	

	printf("\nResult of grep -c %s in file %s: ", argv[1], argv[2]);
	grep_c(argv[2], argv[1]);	

	printf("\nResult of grep -n %s in file %s: ", argv[1], argv[2]);
	grep_n(argv[2], argv[1]);

	printf("\nResult of grep -l %s in file %s: ", argv[1], argv[2]);
	grep_l(argv[2], argv[1]);
	return 0;
}

