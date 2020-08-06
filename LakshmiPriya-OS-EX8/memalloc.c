#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 99999

typedef struct FRAMES
{
	int startaddr;
	int endaddr;
    char status[20];
	int size;
    struct FRAMES *next;
}frames;

void insert(frames **head, frames **tail, int startaddr, int endaddr, char *status)
{
    frames *newnode = (frames*) malloc(sizeof(frames));
	newnode->startaddr = startaddr;
	newnode->endaddr = endaddr;
    strcpy(newnode->status, status);
    newnode->size = endaddr-startaddr;
    newnode->next = NULL;

    if(*head==NULL)
    {
        *head=*tail=newnode;
    }
    else
    {
        (*tail)->next = newnode;
        (*tail) = newnode;
    }
}

int firstFit(frames **alloc_head, frames **free_head, char *pid, int size)
{
	if(*free_head==NULL)
	{
		printf("\nNo free frames");
		return -1;
	}

    frames *ftemp = *free_head;
	frames *prev = NULL;
    int flag=1;
    frames *newnode = (frames*)malloc(sizeof(frames));

    while(ftemp!=NULL &&  size > ftemp->size)
	{
		prev=ftemp;
        ftemp=ftemp->next;
    }

    if(ftemp==NULL)
        flag=0;
    else if(size != ftemp->size)
    {
        strcpy(newnode->status, pid);
		newnode->startaddr = ftemp->startaddr;
		newnode->endaddr = ftemp->startaddr + size;
        newnode->size = size;
		newnode->next = NULL;

		frames *atemp= *alloc_head;

		if(*alloc_head==NULL)
		{
			*alloc_head=newnode;
		}
		else
		{
			frames *sprev=NULL;
			while(atemp!=NULL && atemp->startaddr < ftemp->startaddr)
			{
				sprev=atemp;
				atemp=atemp->next;
			}
			if(sprev==NULL)
			{
				newnode->next=*alloc_head;
				*alloc_head=newnode;
			}
			else
			{
				newnode->next = sprev->next;
				sprev->next = newnode;
			}
		}
        ftemp->size = ftemp->size - size;
		ftemp->startaddr += size; 
    }
    else if(size==ftemp->size)
    {
		frames *atemp= *alloc_head;
	    strcpy(ftemp->status, pid);

		if(prev==NULL)
			*free_head=ftemp->next;
		else
			prev->next=ftemp->next;
		ftemp->next=NULL;

		if(*alloc_head==NULL)
		{
			*alloc_head=ftemp;
		}
		else
		{
			frames *sprev=NULL;
			while(atemp!=NULL && atemp->startaddr < ftemp->startaddr)
			{
				sprev=atemp;
				atemp=atemp->next;
			}
			if(sprev==NULL)
			{
				ftemp->next=*alloc_head;
				*alloc_head=ftemp;
			}
			else
			{
				ftemp->next = sprev->next;
				sprev->next = ftemp;
			}
		}

	    free(newnode);
    }
    return flag;
}

int bestFit(frames **alloc_head, frames **free_head, char *pid, int size)
{
	if(*free_head==NULL)
	{
		printf("\nNo free frames");
		return -1;
	}

    frames *ftemp = *free_head;
	frames *prev = NULL;
    int flag=1;
    frames *newnode = (frames*)malloc(sizeof(frames));

	int minsize=MAX;
	frames *temp= ftemp, *ptemp=NULL;
    while(temp!=NULL)
	{
		if(minsize > temp->size && temp->size >=size)
		{
			minsize=temp->size;
			prev=ptemp;
		    ftemp=temp;
		}

		ptemp=temp;
		temp=temp->next;
    }

    if(ftemp==NULL)
        flag=0;
    else if(size != ftemp->size)
    {
        strcpy(newnode->status, pid);
		newnode->startaddr = ftemp->startaddr;
		newnode->endaddr = ftemp->startaddr + size;
        newnode->size = size;
		newnode->next = NULL;

		frames *atemp= *alloc_head;

		if(*alloc_head==NULL)
		{
			*alloc_head=newnode;
		}
		else
		{
			frames *sprev=NULL;
			while(atemp!=NULL && atemp->startaddr < ftemp->startaddr)
			{
				sprev=atemp;
				atemp=atemp->next;
			}
			if(sprev==NULL)
			{
				newnode->next=*alloc_head;
				*alloc_head=newnode;
			}
			else
			{
				newnode->next = sprev->next;
				sprev->next = newnode;
			}
		}
        ftemp->size = ftemp->size - size;
		ftemp->startaddr += size; 
    }
    else if(size==ftemp->size)
    {
		frames *atemp= *alloc_head;
	    strcpy(ftemp->status, pid);

		if(prev==NULL)
			*free_head=ftemp->next;
		else
			prev->next=ftemp->next;
		ftemp->next=NULL;

		if(*alloc_head==NULL)
		{
			*alloc_head=ftemp;
		}
		else
		{
			frames *sprev=NULL;
			while(atemp!=NULL && atemp->startaddr < ftemp->startaddr)
			{
				sprev=atemp;
				atemp=atemp->next;
			}
			if(sprev==NULL)
			{
				ftemp->next=*alloc_head;
				*alloc_head=ftemp;
			}
			else
			{
				ftemp->next = sprev->next;
				sprev->next = ftemp;
			}
		}

	    free(newnode);
    }
    return flag;
}

int worstFit(frames **alloc_head, frames **free_head, char *pid, int size)
{
	if(*free_head==NULL)
	{
		printf("\nNo free frames");
		return -1;
	}

    frames *ftemp = *free_head;
	frames *prev = NULL;
    int flag=1;
    frames *newnode = (frames*)malloc(sizeof(frames));

	int maxsize=-MAX;
	frames *temp= ftemp, *ptemp=NULL;
    while(temp!=NULL)
	{
		if(maxsize < temp->size && temp->size >= size)
		{
			maxsize=temp->size;
			prev=ptemp;
		    ftemp=temp;
		}

		ptemp=temp;
		temp=temp->next;
    }

    if(ftemp==NULL)
        flag=0;
    else if(size != ftemp->size)
    {
        strcpy(newnode->status, pid);
		newnode->startaddr = ftemp->startaddr;
		newnode->endaddr = ftemp->startaddr + size;
        newnode->size = size;
		newnode->next = NULL;

		frames *atemp= *alloc_head;

		if(*alloc_head==NULL)
		{
			*alloc_head=newnode;
		}
		else
		{
			frames *sprev=NULL;
			while(atemp!=NULL && atemp->startaddr < ftemp->startaddr)
			{
				sprev=atemp;
				atemp=atemp->next;
			}
			if(sprev==NULL)
			{
				newnode->next=*alloc_head;
				*alloc_head=newnode;
			}
			else
			{
				newnode->next = sprev->next;
				sprev->next = newnode;
			}
		}
        ftemp->size = ftemp->size - size;
		ftemp->startaddr += size; 
    }
    else if(size==ftemp->size)
    {
		frames *atemp= *alloc_head;
	    strcpy(ftemp->status, pid);

		if(prev==NULL)
			*free_head=ftemp->next;
		else
			prev->next=ftemp->next;
		ftemp->next=NULL;

		if(*alloc_head==NULL)
		{
			*alloc_head=ftemp;
		}
		else
		{
			frames *sprev=NULL;
			while(atemp!=NULL && atemp->startaddr < ftemp->startaddr)
			{
				sprev=atemp;
				atemp=atemp->next;
			}
			if(sprev==NULL)
			{
				ftemp->next=*alloc_head;
				*alloc_head=ftemp;
			}
			else
			{
				ftemp->next = sprev->next;
				sprev->next = ftemp;
			}
		}

	    free(newnode);
    }
    return flag;
}

void dealloc(frames **alloc_head, frames **free_head, char *pid)
{
    frames *atemp = *alloc_head;
    int flag=0;
	frames *aprev=NULL;
    while(atemp!=NULL)
    {
        if(strcmp(atemp->status, pid)==0)
        {
			strcpy(atemp->status, "H");
			if(aprev==NULL)
				*alloc_head=atemp->next;
			else
				aprev->next=atemp->next;

			frames *ftemp=*free_head;
			frames *sprev=NULL;
			while(ftemp!=NULL && atemp->startaddr > ftemp->startaddr)
			{
				sprev=ftemp;
				ftemp=ftemp->next;
			}

			frames *next=atemp->next;
			if(sprev==NULL)
			{
				atemp->next=*free_head;
				*free_head=atemp;
			}
			else
			{
				atemp->next = sprev->next;
				sprev->next = atemp;
			}
			
            flag=1;
			atemp=next;
        }
		else
		{
			aprev=atemp;
			atemp=atemp->next;
		}
    }
    if(flag==0)
	{
        printf("\n\nProcess ID NOT found!\n");
		return;
	}
	printf("\n\nSpace deallocated!!\n");
}

void print_mem(frames **head)
{
    frames *node=*head;
	printf("\n-----------------------------------------------------------------------------------------------------------\n");
    while(node!=NULL)
    {
        printf("|%-*s|\t", node->endaddr - node->startaddr+5, node->status);
        node=node->next;
    }
	printf("\n-----------------------------------------------------------------------------------------------------------\n");
	node=*head;
    while(node!=NULL)
    {
		printf("%-d%*d\t", node->startaddr, node->endaddr - node->startaddr+5, node->endaddr);
        node=node->next;
    }
}

void print_phymem(frames **alloc_head, frames **free_head)
{
    frames *atemp=*alloc_head;
    frames *ftemp=*free_head;
	frames *node=NULL;
	
	printf("\n-----------------------------------------------------------------------------------------------------------\n");

	while(atemp!=NULL && ftemp!=NULL)
	{
		if(atemp->startaddr < ftemp->startaddr)
		{	
			node=atemp;
			atemp=atemp->next;
		}
		else
		{	
			node=ftemp;
			ftemp=ftemp->next;
		}
	    printf("|%-*s|\t", node->endaddr - node->startaddr+5, node->status);
	}

	if(atemp!=NULL)
		node=atemp;
	else if(ftemp!=NULL)
		node=ftemp;
	if(node!=NULL)
	{
		while(node!=NULL)
		{
			printf("|%-*s|\t", node->endaddr - node->startaddr+5, node->status);
			node=node->next;
		}
	}
	printf("\n-----------------------------------------------------------------------------------------------------------\n");

	atemp=*alloc_head;
    ftemp=*free_head;
	while(atemp!=NULL && ftemp!=NULL)
	{
		if(atemp->startaddr < ftemp->startaddr)
		{	
			node=atemp;
			atemp=atemp->next;
		}
		else
		{	
			node=ftemp;
			ftemp=ftemp->next;
		}
		printf("%-d%*d\t", node->startaddr, node->endaddr - node->startaddr+5, node->endaddr);
	    node=node->next;
	}
	
	if(atemp!=NULL)
		node=atemp;
	else if(ftemp!=NULL)
		node=ftemp;
	if(node!=NULL)
	{
		while(node!=NULL)
		{
			printf("%-d%*d\t", node->startaddr, node->endaddr - node->startaddr+5, node->endaddr);
		    node=node->next;
		}
	}
}

void print_list(frames **alloc_head, frames **free_head)
{
	printf("\n\nAllotted Memory -->");
    print_mem(alloc_head);
	printf("\n\nFree Memory -->");
    print_mem(free_head);
	printf("\n\nPhysical Memory -->");
    print_phymem(alloc_head, free_head);
}

void coalesce(frames **free_head)
{
    frames *temp= *free_head;
    while(temp!=NULL && temp->next!=NULL)
    {
        if(temp->endaddr==temp->next->startaddr)
        {
            frames *del=temp->next;
			temp->endaddr=temp->next->endaddr;
			temp->size += temp->next->size;
			temp->next=temp->next->next;
			free(del);
        }
        temp=temp->next;
    }
}

int main()
{
    frames *free_head = NULL;
    frames *free_tail = NULL;
	frames *alloc_head = NULL;
	frames *alloc_tail = NULL;

    int n, size, res, ch, choice;
	char pid[20];

    printf("Enter number of partitions: ");
    scanf("%d",&n);

    int startaddr, endaddr;

    for( int i=0;i<n;i++ )
    {
        printf("Enter starting address of frame %d : ", i);
        scanf("%d", &startaddr);
        printf("Enter ending address of frame %d   : ", i);
        scanf("%d", &endaddr);
        insert(&free_head, &free_tail, startaddr, endaddr, "H");
    }

    printf("\nFREE POOL MEMORY\n");
    print_mem(&free_head);
    printf("\n\n");

    do
    {
        printf("\nMenu:");
        printf("\n1.Entry / Allocate");
        printf("\n2.Exit / Deallocate");
        printf("\n3.Display");
        printf("\n4.Coalescing of Holes");
        printf("\n5.Exit");
        int k;
        printf("\nEnter Choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            {
                printf("\nEnter PID: ");
                scanf(" %[^\n]", pid);
                printf("Enter size of process: ");
                scanf("%d",&size);

                printf("\nMemory Allocation Algorithm:");
                printf("\n\t1.First Fit");
                printf("\n\t2.Best Fit");
                printf("\n\t3.Worst Fit");
                printf("\nEnter Choice: ");
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1:
                    {
                        res=firstFit(&alloc_head, &free_head, pid, size);
                        if(!res) 
							printf("\nProcess cannot be allocated!");
						print_list(&alloc_head, &free_head);
                        break;
                    }
                    case 2:
                    {
              			res=bestFit(&alloc_head, &free_head, pid, size);
                        if(!res) 
							printf("\nProcess cannot be allocated!");
						print_list(&alloc_head, &free_head);
                        break;
                    }
                    case 3:
                    {
						res=worstFit(&alloc_head, &free_head, pid, size);
                        if(!res) 
							printf("\nProcess cannot be allocated!");
						print_list(&alloc_head, &free_head);
                        break;
                    }
                    default : printf("\nInvalid Choice!");
                }
                break;
            }
            case 2:
		            printf("\nEnter PID to deallocate: ");
		            scanf(" %[^\n]", pid);
		            dealloc(&alloc_head, &free_head, pid);
					print_list(&alloc_head, &free_head);
		            break;
  
            case 3:
					printf("\nPhysical Memory -->\n");
                    print_phymem(&alloc_head, &free_head);
		            break;
            
            case 4:
		            coalesce(&free_head);
					printf("\nFree Memory -->\n");
		            print_mem(&free_head);
		            break;
            
            case 5: 
                	break;

            default : printf("\nInvalid choice!");
        }
    }while(ch!=5);

    return 0;
}

