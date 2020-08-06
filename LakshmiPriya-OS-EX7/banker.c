#include <stdio.h>
#include <stdlib.h>

void resourceNeed(int n, int m, int max[n][m], int allocation[n][m], int need[n][m])
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			need[i][j]=max[i][j]-allocation[i][j];
}

int banker(int n, int m, int available[m], int allocation[n][m], int need[n][m], int safeseq[n])
{
	int count=0;
	int completed[n];
	int sindex=0, check=0;

	int i, j;

	for(i=0;i<n;i++)
		completed[i]=0;

	while(count!=n)
	{
		check=0;
		for(i=0;i<n;i++)
		{
			if(completed[i]==0)
			{
				for(j=0;j<m;j++)
					if(need[i][j]>available[j])
						break;
				if(j==m)
				{
					completed[i]=1;
					safeseq[sindex++]=i;
					count++;
					check=1;

					for(j=0;j<m;j++)
						available[j] += allocation[i][j];
					
					break;
				}
			}	
		}
		
		if(check==0)
		{
			printf("\n\nNO safe sequence!!\n");
			return -1;
		}
	}
	
}

void printData(int n, int m, char process[n][20], char resource[m][20], int allocation[n][m], int max[n][m], int need[n][m], int available[m])
{
	int i, j;

	printf("\n%-10s%-*s\t%-*s\t%-*s\t%-*s\n", "PID", 3*m, "Alloc", 3*m, "Max", 3*m, "Need", 3*m, "Avail");

	for(i=0;i<5;i++)
	{
		if(i==0)
			printf("%-10s", "");
		else
		{
			for(j=0;j<m;j++)
				printf("%-3s", resource[j]);
			printf("\t");
		}
	}
	printf("\n");

	for(i=0;i<n;i++)
	{
		printf("%-10s", process[i]);
		for(j=0;j<m;j++)
			printf("%-3d", allocation[i][j]);
		printf("\t");
		for(j=0;j<m;j++)
			printf("%-3d", max[i][j]);
		printf("\t");
		for(j=0;j<m;j++)
			printf("%-3d", need[i][j]);
		printf("\t");
		if(i==0)
			for(j=0;j<m;j++)
				printf("%-3d", available[j]);
		printf("\n");
	}
}


void main()
{

	int n, m;
	printf("\nNumber of processes: ");
	scanf(" %d", &n);

	printf("\nNumber of resources: ");
	scanf(" %d", &m);

	int i,j;
	int available[m], max[n][m], allocation[n][m];
	int need[n][m];
	int safeseq[n];
	int choice=0, res;
	char process[n][20];
	char resource[m][20];
	
	printf("\n\nBanker's Algorithm:\n\t1. Read Data\n\t2. Print Data\n\t3. Safety Sequence\n\t4. Exit\nEnter choice: ");
	scanf("%d", &choice);

	while(choice!=4)
	{
		switch(choice)
		{	
			case 1: 
					printf("\n\n");
					for(int i=0;i<n;i++)
					{
						printf("Enter process name: ");
						scanf(" %[^\n]", process[i]);
					}

					printf("\n\n");
					for(int i=0;i<m;i++)
					{
						printf("Enter resource name: ");
						scanf(" %[^\n]", resource[i]);
						printf("Enter number of available instances of %s: ", resource[i]);
						scanf(" %d", &available[i]);
					}

					printf("\n\n");
					for(int i=0;i<n;i++)
					{
						printf("Maximum requirement for %s: ", process[i]);
						for(int j=0;j<m;j++)
							scanf(" %d", &max[i][j]);
					}

					printf("\n\n");
					for(int i=0;i<n;i++)
					{
						printf("Allocated instances to %s: ", process[i]);
						for(int j=0;j<m;j++)
							scanf(" %d", &allocation[i][j]);
					}
					
					resourceNeed(n, m, max, allocation, need);
					break;

			case 2: 
					printData(n, m, process, resource, allocation, max, need, available);
					break;

			case 3: 
					res=banker(n, m, available, allocation, need, safeseq);
					if(res!=-1)
					{
						printf("\nSafe Sequence: ");
						for(int i=0;i<n;i++)
							printf("\t%d", safeseq[i]);
					}
					printf("\n");
					break;
	
			case 4: return;	
	
			default: printf("\nInvalid option!!");
		}

		printf("\n\nBanker's Algorithm:\n\t1. Read Data\n\t2. Print Data\n\t3. Safety Sequence\n\t4. Exit\nEnter choice: ");
		scanf("%d", &choice);
	}


/*
	int n=5;
	int m=3;
	int i,j;
	int need[n][m], safeseq[n];

	
	int available[3]={3,3,2};
	int max[5][3]={
					{7,5,3},
					{3,2,2},
					{9,0,2},
					{2,2,2},
					{4,3,3}
				  };
	int allocation[5][3]={
							{0,1,0},
							{2,0,0},
							{3,0,2},
							{2,1,1},
							{0,0,2}
			             };

	char process[5][5]={"p0", "p1", "p2", "p3", "p4"};
	char resource[3][5]={"A", "B", "C"};

	resourceNeed(n, m, max, allocation, need);
	
	printData(n, m, process, resource, allocation, max, need, available);


	int res=banker(n, m, available, allocation, need, safeseq);

	printf("\nSafe Sequence: ");
	if(res!=-1)
		for(int i=0;i<n;i++)
			printf("\t%d", safeseq[i]);
	printf("\n");
*/	
}
