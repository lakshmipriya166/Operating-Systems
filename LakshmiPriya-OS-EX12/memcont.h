#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct DIRECTORY
{
	char file[20];
	int start;
	int len;
	struct DIRECTORY *next;
}cdirec;

int cfindspace(int n, int blocks[n], int size, int start, int *freeblocks)
{
	int count=0;

	for(int i=start;i<n;i++)
	{
		if(blocks[i]==0)
			count++;
		else
			count=0;
		if(count==size)
		{
			printf("\nBlocks before allocation: ");
			for(int k=0;k<n;k++)
				printf("\t%d", blocks[k]);

			for(int j=i-count+1;j<=i;j++)
				blocks[j]=1;

			printf("\nBlocks after allocation: ");			
			for(int k=0;k<n;k++)
				printf("\t%d", blocks[k]);

			*freeblocks -= count;

			return i-count+1;
		}
	}
	return -1;
}

void cprintDir(cdirec*dir)
{
	cdirec*temp=dir->next;
	if(temp==NULL)
	{
		printf("\n\nDirectory empty!\n");
		return;
	}
	printf("\n\nDIRECTORY:");
	printf("\n%-15s%-10s%-10s", "File Name", "Start", "Length");
	while(temp!=NULL)
	{
	printf("\n%-15s%-10d%-10d", temp->file, temp->start, temp->len);
		temp=temp->next;
	}
	printf("\n");
}

void memcont()
{
	int memsize, bsize, nfiles;
	char file[20];
	int size;

	printf("\nMain Memory size: ");
	scanf("%d", &memsize);
	printf("\nSize of each block in the disk: ");
	scanf("%d", &bsize);
	
	int nblocks=memsize/bsize;

	cdirec* dir=(cdirec*)malloc(sizeof(cdirec));
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
		scanf(" %[^\n]", file);
		printf("\nSize of file%d: ", i+1);
		scanf(" %d", &size);

		int n=ceil((float)size/bsize);
		if(freeblocks<n)
		{
			printf("\nNot enough memory error!");
			continue;
		}

		int r=1000;
		while(r>0)
		{
			int start=rand()%nblocks;
			int index=cfindspace(nblocks, blocks, n, start, &freeblocks);
			if(index!=-1)
			{
				cdirec* d=(cdirec*)malloc(sizeof(cdirec));
				strcpy(d->file, file);
				d->start=index;
				d->len=n;
				d->next=dir->next;
				dir->next=d;
				printf("\nAllocated!");
				break;
			}
			r--;
		}
		if(r==0)
			printf("\nNot enough memory error!");
	}

	cprintDir(dir);

}

