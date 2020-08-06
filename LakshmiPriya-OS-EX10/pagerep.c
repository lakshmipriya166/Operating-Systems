#include <stdio.h>
#include <stdlib.h>
#define MAX 9999999

typedef struct NODE
{
	int data;
	struct NODE *next;
}node;

void readinput(int *nfree, int *nframes, int ref[])
{
	printf("\nEnter number of free frames: ");
	scanf("%d", nfree);
	printf("\nEnter number of frames required by process: ");
	scanf("%d", nframes);
	if(*nfree<*nframes)
	{
		printf("\nNot enough free frames!\n");
		return;
	}
	printf("\nEnter reference string(end with -1): ");
	
	int index=0;
	scanf("%d", &ref[index++]);
	while(ref[index-1]!=-1)
		scanf("%d", &ref[index++]);
}

void enqueue(node *head, int data)
{
	node *new=(node *)malloc(sizeof(node));
	new->data=data;
	new->next=NULL;

	node *temp=head->next;
	if(temp==NULL)
	{
		head->next=new;
		return;
	}

	while(temp->data!=data && temp->next!=NULL)
		temp=temp->next;

	if(temp->data==data)
		return;

	if(temp->next==NULL)
		temp->next=new;
}

int dequeue(node *head)
{
	node *del=head->next;
	if(del==NULL)
		return -1;
	int data=del->data;
	free(del);
	head->next=head->next->next;
	return data;
}

void fifo(int ref[], int nframes)
{
	printf("\n\nFIFO PAGE REPLACEMENT ALGORITHM\n");
	node *head=(node *)malloc(sizeof(node));
	head->next=NULL;

	int frames[nframes];
	int filled=0, index=0, i=0, pgfault=0;
	
	printf("%10s%*s\t%s", "Page ref->", 6*nframes, "Memory -> ", "PF");
	while(ref[index]!=-1)
	{
		printf("\n%10d -> ", ref[index]);

		for(i=0;i<filled;i++)
			if(frames[i]==ref[index])
				break;
		if(i!=filled)
		{
			index++;
			for(i=0;i<filled;i++)
				printf("%5d", frames[i]);
			printf("%*s", (nframes-filled+1)*5, "-");
			continue;
		}
	
		pgfault++;

		if(filled<nframes)
		{
			frames[filled++]=ref[index];
			enqueue(head, ref[index]);
		}
		else
		{
			int data=dequeue(head);
			for(i=0;i<filled;i++)
				if(frames[i]==data)
				{
					frames[i]=ref[index];
					enqueue(head, ref[index]);
					break;
				}
		}
		index++;
			
		for(i=0;i<filled;i++)
			printf("%5d", frames[i]);
		printf("%*d", (nframes-filled+1)*5, pgfault);
	}
	printf("\nTotal Number of Page Faults: %d\n", pgfault);
}

int lsearch(int ref[], int start, int data)
{
	int i=start;
	while(ref[i]!=-1)
		if(ref[i++]==data)
			break;
	return i;
}

void optimal(int ref[], int nframes)
{

	printf("\n\nOPTIMAL PAGE REPLACEMENT ALGORITHM\n");
	int frames[nframes];
	int filled=0, index=0, i=0, pgfault=0;
	
	printf("%10s%*s\t%s", "Page ref->", 6*nframes, "Memory -> ", "PF");
	while(ref[index]!=-1)
	{
		printf("\n%d -> ", ref[index]);

		for(i=0;i<filled;i++)
			if(frames[i]==ref[index])
				break;
		if(i!=filled)
		{
			index++;
			for(i=0;i<filled;i++)
				printf("%5d", frames[i]);
			printf("%*s", (nframes-filled+1)*5, "-");
			continue;
		}
	
		pgfault++;

		if(filled<nframes)
			frames[filled++]=ref[index];
		else
		{
			int data;
			int rindex=lsearch(ref, index+1, frames[0]);
			int findex=0;
			for(i=1;i<filled;i++)
			{
				int ind=lsearch(ref, index+1, frames[i]);
				if(ind>rindex)
				{
					rindex=ind;
					findex=i;
				}
			}
			frames[findex]=ref[index];
		}
		index++;
			
		for(i=0;i<filled;i++)
			printf("%5d", frames[i]);
		printf("%*d", (nframes-filled+1)*5, pgfault);
	}
	printf("\nTotal Number of Page Faults: %d\n", pgfault);
}

void lru(int ref[], int nframes)
{
	printf("\n\nLRU PAGE REPLACEMENT ALGORITHM\n");
	int frames[nframes];
	int filled=0, index=0, i=0, pgfault=0;
	int counter=0;
	int freq[20];
	for(i=0;i<20;i++)
		freq[i]=MAX;
	
	printf("%10s%*s\t%s", "Page ref->", 6*nframes, "Memory -> ", "PF");
	while(ref[index]!=-1)
	{
		printf("\n%d -> ", ref[index]);

		for(i=0;i<filled;i++)
			if(frames[i]==ref[index])
				break;
		if(i!=filled)
		{
			freq[ref[index]]=counter;
			counter++;
			index++;
			for(i=0;i<filled;i++)
				printf("%5d", frames[i]);
			printf("%*s", (nframes-filled+1)*5, "-");
			continue;
		}
	
		pgfault++;

		if(filled<nframes)
			frames[filled++]=ref[index];
		else
		{
			int r=freq[frames[0]];
			int findex=0;
			for(i=1;i<filled;i++)
			{
				if(freq[frames[i]] < r)
				{
					r = freq[frames[i]];
					findex=i;
				}
			}
			frames[findex]=ref[index];
		}

		freq[ref[index]]=counter;
		counter++;
		index++;
			
		for(i=0;i<filled;i++)
			printf("%5d", frames[i]);
		printf("%*d", (nframes-filled+1)*5, pgfault);
	}
	printf("\nTotal Number of Page Faults: %d\n", pgfault);
}

void lfu(int ref[], int nframes)
{
	printf("\n\nLFU PAGE REPLACEMENT ALGORITHM\n");
	int frames[nframes];
	int filled=0, index=0, i=0, pgfault=0;
	int freq[20];
	for(i=0;i<20;i++)
		freq[i]=0;
	
	printf("%10s%*s\t%s", "Page ref->", 6*nframes, "Memory -> ", "PF");
	while(ref[index]!=-1)
	{
		printf("\n%d -> ", ref[index]);

		for(i=0;i<filled;i++)
			if(frames[i]==ref[index])
				break;
		if(i!=filled)
		{
			freq[ref[index]]++;
			index++;
			for(i=0;i<filled;i++)
				printf("%5d", frames[i]);
			printf("%*s", (nframes-filled+1)*5, "-");
			continue;
		}
	
		pgfault++;

		if(filled<nframes)
			frames[filled++]=ref[index];
		else
		{
			int frequency=freq[frames[0]];
			int findex=0;
			for(i=1;i<filled;i++)
			{
				if(freq[frames[i]] < frequency)
				{
					frequency = freq[frames[i]];
					findex=i;
				}
			}
			frames[findex]=ref[index];
		}

		freq[ref[index]]++;
		index++;
			
		for(i=0;i<filled;i++)
			printf("%5d", frames[i]);
		printf("%*d", (nframes-filled+1)*5, pgfault);
	}
	printf("\nTotal Number of Page Faults: %d\n", pgfault);
}

void main()
{
	int nfree, nframes, index;
	int ref[30];
	int option;

	printf("\n\nPAGE REPLACEMENT ALGORITHMS\n\t1. READ_INPUT\n\t2. FIFO\n\t3. OPTIMAL\n\t4. LRU\n\t5. LFU\n\t6. EXIT\nEnter your option: ");
	scanf("%d", &option);

	while(option!=6)
	{


		switch(option)
		{
			case 1: readinput(&nfree, &nframes, ref);
					break; 
			case 2: fifo(ref, nframes);
					break;
			case 3: optimal(ref, nframes);
					break;
			case 4: lru(ref, nframes);
					break;
			case 5: lfu(ref, nframes);
					break;
		}
		printf("\n\nPAGE REPLACEMENT ALGORITHMS\n\t1. READ_INPUT\n\t2. FIFO\n\t3. OPTIMAL\n\t4. LRU\n\t5. LFU\n\t6. EXIT\nEnter your option: ");
		scanf("%d", &option);

	}

}
