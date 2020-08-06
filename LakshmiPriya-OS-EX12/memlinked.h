#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int nblocks=0;

typedef struct FILE
{
	char fname[20];
	int start;
	int end;
	int *alloc;
}file;

typedef struct directory
{
	struct FILE *f;
	struct directory *next;
}ldirec;

file *lfindspace(char fname[20], int n, int blocks[n], int size, int *freeblocks)
{
	printf("\nBlocks before allocation: ");
	for(int k=0;k<n;k++)
		printf("\t%d", blocks[k]);


	int j;
	file *f=(file *)malloc(sizeof(file));
	strcpy(f->fname, fname);
	f->alloc=(int *)malloc(size*sizeof(int));
	int index=0;

	while(index<size)
	{
		j=rand()%nblocks;
		if(blocks[j]==0)
		{
			blocks[j]=1;
			f->alloc[index]=j;
			if(index==0)
				f->start=j;
			else if(index==size-1)
				f->end=j;
			index++;
		}
	}
	
	printf("\nBlocks after allocation: ");			
	for(int k=0;k<n;k++)
		printf("\t%d", blocks[k]);

	*freeblocks -= size;
	return f;
}

void lprintDir(ldirec*dir)
{
	ldirec*temp=dir->next;
	if(temp==NULL)
	{
		printf("\n\nDirectory empty!\n");
		return;
	}
	printf("\n\nDIRECTORY:");
	printf("\n%-15s%-10s%-10s", "File Name", "Start", "End");
	while(temp!=NULL)
	{
		file *ftemp=temp->f;
		printf("\n%-15s%-10d%-10d", ftemp->fname, ftemp->start, ftemp->end);
		temp=temp->next;
	}
	printf("\n\nIndividual File listing: ");
	temp=dir->next;
	while(temp!=NULL)
	{
		file *ftemp=temp->f;
		printf("\n%s: ", ftemp->fname);
		int i=0;
		do
		{
			printf("\t%-10d", ftemp->alloc[i++]);
		}while(ftemp->alloc[i-1]!=ftemp->end);

		temp=temp->next;
	}

	printf("\n");
}

void memlinked()
{
	int memsize, bsize, nfiles;
	char fname[20];
	int size;

	printf("\nMain Memory size: ");
	scanf("%d", &memsize);
	printf("\nSize of each block in the disk: ");
	scanf("%d", &bsize);
	
	nblocks=memsize/bsize;

	ldirec*dir=(ldirec*)malloc(sizeof(ldirec));
	dir->next=NULL;

	int blocks[nblocks];

	for(int i=0;i<nblocks;i++)
		blocks[i]=0;
	int freeblocks=nblocks;

	 
	printf("\nEnter number of files to be allocated: ");
	scanf("%d", &nfiles);

	for(int i=0;i<nfiles;i++)
	{
		printf("\n\nName of file%d: ", i+1);
		scanf(" %[^\n]", fname);
		printf("\nSize of file%d: ", i+1);
		scanf(" %d", &size);

		int n=ceil((float)size/bsize);
		if(freeblocks<n)
		{
			printf("\nNot enough memory error!");
			continue;
		}

		while(1)
		{
			ldirec *d=(ldirec*)malloc(sizeof(ldirec));
			d->f=lfindspace(fname, nblocks, blocks, n, &freeblocks);
			d->next=dir->next;
			dir->next=d;
			printf("\nAllocated!");
			break;	
		}
	}

	lprintDir(dir);

}

