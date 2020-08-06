#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FILE
{
	char fname[20];
	struct FILE *loc;
	struct FILE *next;
}file;

typedef struct sdirectory
{
	char dname[20];
	file *fptr;
	struct sdirectory *next;
}sdir;

typedef struct treedirectory
{
	char dname[20];
	struct treedirectory *tdir[3];
	char files[3][20];
	int ndir;
	int nfiles;
}treedir;

void createDir(sdir *dir)
{
	char dname[20];
	printf("\nEnter directory name: ");
	scanf(" %[^\n]", dname);
	sdir *temp=dir->next;
	while(temp!=NULL)
	{
		if(strcmp(temp->dname, dname)==0)
			break;
		temp=temp->next;
	}

	if(temp!=NULL)
	{
		printf("\nDirectory already exists!\n");
		return;
	}

	sdir *d=(sdir *)malloc(sizeof(sdir));
	strcpy(d->dname, dname);
	d->fptr=(file *)malloc(sizeof(file));
	d->fptr->next=NULL;
	d->next=dir->next;
	dir->next=d;
	printf("\nDirectory created!\n");
}

void createFile(sdir *dir)
{
	char dname[20], fname[20];
	printf("\nEnter directory name: ");
	scanf(" %[^\n]", dname);
	sdir *temp=dir->next;
	while(temp!=NULL)
	{
		if(strcmp(temp->dname, dname)==0)
			break;
		temp=temp->next;
	}
	if(temp==NULL)
	{
		printf("\nDirectory not found!\n");
		return;
	}

	printf("\nEnter file name: ");
	scanf(" %[^\n]", fname);

	file *f=temp->fptr->next;

	while(f!=NULL)
	{
		if(strcmp(f->fname, fname)==0)
		{
			printf("\nFile already exists!\n");
			return;
		}
		f=f->next;
	}

	file *ftemp=(file *)malloc(sizeof(file));
	strcpy(ftemp->fname, fname);
	ftemp->loc=ftemp;
	ftemp->next=temp->fptr->next;
	temp->fptr->next=ftemp;
	printf("\nFile created!\n");
}

void dispSdir(sdir *dir)
{
	sdir *temp=dir->next;
	if(temp==NULL)
	{
		printf("\nDirectory empty!\n");
		return;
	}
	
	while(temp!=NULL)
	{
		printf("\n\n%s: ", temp->dname);
		file *f=temp->fptr->next;
		printf("\n%-20s%-10s", "File Name", "Location");
		while(f!=NULL)
		{
			printf("\n%-20s%-10p", f->fname, f->loc);
			f=f->next;
		}
		temp=temp->next;
	}
	printf("\n");
}

treedir *createRoot()
{
	treedir *root=(treedir *)malloc(sizeof(treedir));
	printf("\nEnter root directory name: ");
	scanf(" %[^\n]", root->dname);
	root->ndir=0;
	root->nfiles=0;
	return root;
}
void createDirTreeDir(treedir *root)
{
	int i;
	char path[200];
	printf("\nEnter path to directory(/root/../): ");
	scanf(" %[^\n]", path);

    treedir *temp=root;
    char *token = strtok(path,"/");

    token = strtok(NULL,"/");

    while(token!=NULL) 
	{
		treedir *prev=temp;
		for(i=0;i<temp->ndir;i++)
			if(temp->tdir[i]!=NULL && strcmp(token, temp->tdir[i]->dname)==0)				
				temp=temp->tdir[i];

		if(temp==prev)
		{
			printf("\nInvalid path\n");
			return;
		}
		
        token = strtok(NULL,"/");
    }

    if(token==NULL && temp!=NULL)
    {
        if(temp->ndir<3)
        {
            char dname[20];
            printf("Enter the directory name: ");
            scanf("%s", dname);

			for(i=0;i<temp->ndir;i++)
				if(strcmp(temp->tdir[i]->dname, dname)==0)
					break;
			if(i!=temp->ndir)
			{
				printf("\nDirectory exists!\n");
				return;
			}

            treedir *newdir = (treedir *)malloc(sizeof(treedir));
            strcpy(newdir->dname, dname);

			temp->tdir[temp->ndir++]=newdir;
			
			printf("\nDirectory created!\n");
        }
        else 
			printf("\nDirectory limit exceeded!\n");
    }
}

void createFileTreeDir(treedir *root)
{
	int i;
	char path[200];
	printf("\nEnter path to file(/root/../): ");
	scanf(" %[^\n]", path);

    treedir *temp=root;
    char *token = strtok(path, "/");
    token = strtok(NULL,"/");
    while(token != NULL) 
	{
		treedir *prev=temp;
		for(i=0;i<temp->ndir;i++)
			if(temp->tdir[i]!=NULL && strcmp(token, temp->tdir[i]->dname)==0)
				temp=temp->tdir[i];
		
		if(temp==prev)
		{
			printf("\nInvalid path\n");
			return;
		}

        token = strtok(NULL,"/");
    }
    if(token == NULL && temp!=NULL)
    {
        if(temp->nfiles < 3)
        {
            char fname[20];
            printf("\nEnter file name: ");
            scanf("%s", fname);

			for(i=0;i<temp->nfiles;i++)
				if(strcmp(temp->files[i], fname)==0)
					break;
			if(i!=temp->nfiles)
			{
				printf("\nFile exists!");
				return;
			}

            strcpy(temp->files[temp->nfiles++], fname);			
			printf("\nFile created!\n");
        }
        else
            printf("\nFile limit exceeded!\n");
    }
	else
		printf("\nPath does not exist!\n");
}

void dispTreeDir(treedir *root)
{
	if(root==NULL)
		return;
	printf("\nDirectory name : %s", root->dname);
	printf("\nFiles          :");
	for(int j=0;j < root->nfiles;j++)
		printf("\t%s", root->files[j]);
	printf("\nSub directories:");
	for(int k=0;k < root->ndir;k++)
		printf("\t%s", root->tdir[k]->dname);

	printf("\n\n");

	for(int k=0;k < root->ndir;k++)
		dispTreeDir(root->tdir[k]);

	printf("\n");
}


void main()
{
	int choice, option;
	printf("\n\nFile Organization techniques\n\t1. Single Level Directory\n\t2. Tree structures directory\n\t3. Exit\nEnter your option: ");
	scanf("%d", &choice);
	
	sdir *dir=(sdir *)malloc(sizeof(sdir));
	dir->next=NULL;

	while(choice!=3)
	{
		switch(choice)
		{
			case 1: printf("\n1. Create a directory\n2. Create a file\n3. List the directory structure\n4. Back\nEnter your option: ");
					scanf("%d",&option);
					while(option!=4)
					{
						switch(option)
						{
							case 1: createDir(dir);
									break; 
							case 2: createFile(dir);
									break; 
							case 3: dispSdir(dir);
									break; 
							default: printf("\n\nInvalid Option!\n");
						}
						printf("\n1. Create a directory\n2. Create a file\n3. List the directory structure\n4. Back\nEnter your option: ");
						scanf("%d",&option);
					
					}
					break;

			case 2: 
			{
					treedir *root=createRoot();

					printf("\n1. Create a directory\n2. Create a file\n3. List the directory structure\n4. Back\nEnter your option: ");
					scanf("%d",&option);
					while(option!=4)
					{
						switch(option)
						{
							case 1: createDirTreeDir(root);
									break; 
							case 2: createFileTreeDir(root);
									break; 
							case 3: dispTreeDir(root);
									break; 
							default: printf("\n\nInvalid Option!\n");
						}
						printf("\n1. Create a directory\n2. Create a file\n3. List the directory structure\n4. Back\nEnter your option: ");
						scanf("%d",&option);
					
					}
			}
		}

	printf("\n\nFile Organization techniques\n\t1. Single Level Directory\n\t2. Tree structures directory\n\t3. Exit\nEnter your option: ");
	scanf("%d", &choice);
	}
}
