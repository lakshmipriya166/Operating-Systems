#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void ls(char argv[])
{
	struct dirent *de;
	DIR *dr=opendir(argv);
	if (dr==NULL)
	{
		printf("\nCould not open directory: %s\n", argv);
		exit(1);
	}
	while((de=readdir(dr)) != NULL)
	{
		if(de->d_name[0] != '.')
			printf("%-30s", de->d_name);
	}
	closedir(dr);

}

void ls_a(char argv[])
{
	struct dirent *de;
	DIR *dr=opendir(argv);
	if (dr==NULL)
	{
		printf("\nCould not open directory: %s\n", argv);
		exit(1);
	}
	while((de=readdir(dr)) != NULL)
		printf("%-30s", de->d_name);
	closedir(dr);
	
}

void ls_1(char argv[])
{
	struct dirent *de;
	DIR *dr=opendir(argv);
	if (dr==NULL)
	{
		printf("\nCould not open directory: %s\n", argv);
		exit(1);
	}
	while((de=readdir(dr)) != NULL)
	{
		if(de->d_name[0] != '.')
			printf("%s\n", de->d_name);
	}
	closedir(dr);

}

int main(int argc, char *argv[])
{
	for(int i=1;i<argc;i++)
	{
		printf("\n\nFILE : %s\n", argv[i]);
		printf("\nResult of ls:\n");
		ls(argv[i]);
		printf("\n\nResult of ls -a:\n");
		ls_a(argv[i]);
		printf("\n\nResult of ls -1:\n");
		ls_1(argv[i]);

	}

	return 1;
}
