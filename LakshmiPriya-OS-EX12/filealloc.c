#include "memcont.h"
#include "memlinked.h"
#include "memindex.h"

void main()
{
	int choice;

	printf("\n\nFILE ALLOCATION TECHNIQUES:\n\t1. Contiguous\n\t2. Linked\n\t3. Indexed\n\t4. Exit\nChoose the Allocation scheme: ");
	scanf("%d", &choice);

	while(choice!=4)
	{
		switch(choice)
		{
			case 1: memcont();
					break;
			case 2: memlinked();
					break;
			case 3: memindex();
					break;
			default: printf("\n\nInvalid choice!\n");
		}
		printf("\n\nFILE ALLOCATION TECHNIQUES:\n\t1. Contiguous\n\t2. Linked\n\t3. Indexed\n\t4. Exit\nChoose the Allocation scheme: ");
		scanf("%d", &choice);
	}
}

