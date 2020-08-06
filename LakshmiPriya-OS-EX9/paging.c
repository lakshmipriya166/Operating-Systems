#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct PROCESS
{
	char pid[10];
	int size;
	int pages;
	int *alloc;
	struct PROCESS *next;
}process;

int deallocate(process *proc, char pid[10], int *freeframes, int nfree)
{
	process *temp=proc;
	if(temp->next==NULL)
	{

		printf("\nDeallocation not possible!");
		return -1;
	}
	while(temp->next!=NULL && strcmp(temp->next->pid, pid)!=0)
			temp=temp->next;

	if(temp!=NULL)
	{		
		process *del=temp->next;
		temp->next=del->next;

		for(int i=nfree; i<nfree+del->pages; i++)
			freeframes[i]=del->alloc[i-nfree];

		nfree += del->pages;
		free(del);

		printf("\nDeallocated process %s", pid);
	}
	else
		printf("\nProcess NOT found!");

	return nfree;
}

void printpagetable(process *proc)
{
	process *temp=proc->next;
	if(temp==NULL)
		printf("\nNo user process in page table");

	while(temp!=NULL)
	{
		printf("\n\nPage table for %s", temp->pid);
		for(int i=0;i<temp->pages;i++)
			printf("\nPage %d: Frame: %d", i, temp->alloc[i]);
		temp=temp->next;
	}
}


void printfreeframes(int *freeframes, int nfree)
{
	printf("\nFree Frames: ");
	if(freeframes==NULL)
	{
		printf("\nNO free frames!");
		return;
	}

	for(int i=0;i<nfree;i++)
		printf("%d\t", freeframes[i]);
}


void main()
{
	int physize, pagesize, random;
	
	printf("\nPAGING TECHNIQUE\n");
	printf("\nEnter the physical memory size (in kB): ");
	scanf("%d", &physize);
	printf("\nEnter the page size (in kB): ");
	scanf("%d", &pagesize);
	
	int nframes=physize/pagesize;

	int frames[nframes];
	process *proc=(process *)malloc(sizeof(process));
	
	for(int i=0;i<nframes;i++)
		frames[i]=0;

	printf("\nPhysical memory is divided into %d frames", nframes);

	int nalloc=rand()%nframes;
	for(int i=0;i<nalloc;i++)
	{
		random=rand()%nframes;
		frames[random]=1;
	}
	int nfree=nframes-nalloc;
	printf("\nAfter initialization...\nFREE FRAMES: ");
	int *freeframes=(int *)malloc(100*sizeof(int));
	int findex=0;
	for(int i=0;i<nframes;i++)
		if(frames[i]==0)
		{
			freeframes[findex++]=i;
			printf("%d\t", i);
		}
	printf("\n");

	int choice ;
	printf("\n\nChoices:\n\t1. Process request\n\t2. Deallocation\n\t3. Page Table display for all input process\n\t4. Free Frame list display\n\t5. Exit\nEnter the option :");
	scanf("%d", &choice);
	
	while(choice!=5)
	{
		switch(choice)
		{
			case 1: 
			{
				process *p = (process *)malloc(sizeof(process));
				printf("Enter the Process ID  : ");
				scanf(" %[^\n]", p->pid);
				printf("Enter Page size(in kB): ");
				scanf(" %d", &p->size);
				p->pages=ceil((float)p->size/pagesize);
				
				if(p->pages<=nfree)
				{
					printf("\nProcess is divided into %d pages", p->pages);
					printf("\nPage table for %s: ", p->pid);
					p->alloc=(int *)malloc(p->pages*sizeof(int));
						
					for(int i=0;i<p->pages;i++)
					{
						p->alloc[i]=freeframes[0];
						freeframes=&freeframes[1];
						printf("\nPage %d: Frame: %d", i, p->alloc[i]);
					}
					p->next=proc->next;
					proc->next=p;
					nfree-=p->pages;
				}
				else
				{
					printf("\nFree frames not available!\n");
					free(p);
				}
				break;
			}
			case 2: 
			{
				char pid[10];
				printf("\nEnter the process ID to be de-allocated:");
				scanf(" %[^\n]", pid);
				int res=deallocate(proc, pid, freeframes, nfree);
				if(res!=-1)
					nfree=res;
				break;
			}
			case 3: printpagetable(proc);
					break;
			case 4: printfreeframes(freeframes, nfree);
					break;

			default: printf("\nInvalid choice!");
		}
		printf("\n\nChoices:\n\t1. Process request\n\t2. Deallocation\n\t3. Page Table display for all input process\n\t4. Free Frame list display\n\t5. Exit\nEnter the option:");
		scanf("%d", &choice);

	}
	

} 

