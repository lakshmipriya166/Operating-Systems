#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct DIR
{	
	char fname[20];
	int indexblock;
	int *alloc;
	int nalloc;
	struct DIR *next;
}direc;

void ifindspace(direc *dir, char fname[20], int n, int blocks[n], int size, int *freeblocks)
{
	printf("\nBlocks before allocation: ");
	for(int k=0;k<n;k++)
		printf("\t%d", blocks[k]);

	int j;
	direc *d=(direc *)malloc(sizeof(direc));
	strcpy(d->fname, fname);
	d->indexblock=-1;
	d->alloc=(int *)malloc((size-1)*sizeof(int)); //allocate size excluding index block
	d->nalloc=size-1;
	d->next=dir->next;
	dir->next=d;

	int index=0;

	while(index<size-1)
	{
		j=rand()%n;
		if(blocks[j]==0)
		{
			blocks[j]=1;
			if(d->indexblock==-1)
			{
				d->indexblock=j;
				continue;
			}

			d->alloc[index]=j;
			index++;
		}
	}
	
	printf("\nBlocks after allocation: ");			
	for(int k=0;k<n;k++)
		printf("\t%d", blocks[k]);

	*freeblocks -= size;
}

void iprintDir(direc *dir)
{
	direc *temp=dir->next;
	if(temp==NULL)
	{
		printf("\n\nDirectory empty!\n");
		return;
	}
	printf("\n\nDIRECTORY:");
	printf("\n%-15s%-10s", "File Name", "Block Indexed");
	while(temp!=NULL)
	{
		printf("\n%-15s%-10d", temp->fname, temp->indexblock);
		temp=temp->next;
	}
	printf("\n\nIndividual File index listing: ");
	temp=dir->next;

	while(temp!=NULL)
	{
		printf("\n%s: ", temp->fname);
		for(int i=0;i<temp->nalloc;i++)
			printf("%d\t", temp->alloc[i]);

		temp=temp->next;
	}

	printf("\n");
}

void memindex()
{
	int memsize, bsize, nfiles;
	char fname[20];
	int size;

	printf("\nMain Memory size: ");
	scanf("%d", &memsize);
	printf("\nSize of each block in the disk: ");
	scanf("%d", &bsize);
	
	int nblocks=memsize/bsize;

	direc *dir=(direc *)malloc(sizeof(direc));
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

		int n=ceil((float)size/bsize)+1; //one block for index block
		if(freeblocks<n)
		{
			printf("\nNot enough memory error!");
			continue;
		}

		while(1)
		{
			ifindspace(dir, fname, nblocks, blocks, n, &freeblocks);
			printf("\nAllocated!");
			break;	
		}
	}

	iprintDir(dir);

}

