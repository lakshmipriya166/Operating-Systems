#include <stdio.h>
#include <string.h>
#define MAX 999999999

typedef struct 
{
	char pid[20];
	float arrival_time;
	float burst_time;
}jobs;


void atSort(int n, jobs job[n])
{
	jobs temp;
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(job[i].arrival_time > job[j].arrival_time)
			{
				temp = job[i];
				job[i] = job[j];
				job[j] = temp;
			}
		}
	}
}


void abtSort(int n, jobs job[n])
{
	float time=0;
	int flag=0;
	jobs temp;

	for(int i=0;i<n-1;i++)
	{
		flag = 0;
		for(int j=i+1;j<n;j++)
		{
			if(job[i].burst_time > job[j].burst_time && job[j].arrival_time<=time)
			{
				temp = job[i];
				job[i] = job[j];
				job[j] = temp;
			}
			flag = 1;
		}
		if(flag == 1)
			time += job[i].burst_time;
		else
		{
			time += 1;
			i -= 1;
		}
	}
}


void findWaitingTime(int n, jobs job[n], float wt[]) 
{ 
	float service_time[n];
	service_time[0] = 0;
	wt[0] = 0; 

	for (int i = 1; i < n ; i++) 
	{ 
		service_time[i] = service_time[i-1] + job[i-1].burst_time; 
	
		wt[i] = service_time[i] - job[i].arrival_time; 

		if (wt[i] < 0) 
			wt[i] = 0; 	
	} 
} 


void findTurnAroundTime(int n, jobs job[n], float wt[], float tat[]) 
{ 
	for (int i = 0; i < n ; i++) 
		tat[i] = job[i].burst_time + wt[i]; 
} 


void fcfs(int n, jobs job[n]) 
{ 
	float wt[n], tat[n]; 

	atSort(n, job);
	findWaitingTime(n, job, wt); 

	findTurnAroundTime(n, job, wt, tat); 

	printf("\n%10s\t%10s\t%10s\t%10s\t%10s", "Process ID", "Arrival Time", "Burst Time", "Waiting Time", "Turnaround Time");
		
	float total_wt = 0, total_tat = 0; 
	for (int i = 0 ; i < n ; i++) 
	{ 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
		printf("\n%10s\t%10.0f\t%10.0f\t%10.0f\t\t%10.0f", job[i].pid,  job[i].arrival_time, job[i].burst_time, wt[i], tat[i]);
	} 

	printf("\nAverage Waiting time    = %f", total_wt/n); 
	printf("\nAverage Turnaround time = %f\n\n", total_tat/n); 

    printf("GANTT CHART\n");

	printf("\n");
	for(int i=0;i<n;i++)
		printf("-----------------");
	printf("\n");

    for(int i=0;i<n;i++)	
		printf("|\t%-10s", job[i].pid);
    printf("|");

	printf("\n");
	for(int i=0;i<n;i++)
		printf("-----------------");
	printf("\n");

	printf("%-10.2f", 0.0);
    for(int i=0;i<n;i++)	
		printf("\t%-10.2f", tat[i]+job[i].arrival_time);

	printf("\n\n");

}


void sjfnp(int n, jobs job[n])
{
	float wt[n], tat[n]; 

	abtSort(n, job);
	findWaitingTime(n, job, wt); 

	findTurnAroundTime(n, job, wt, tat); 

	printf("\n%10s\t%10s\t%10s\t%10s\t%10s", "Process ID", "Arrival Time", "Burst Time", "Waiting Time", "Turnaround Time");
		
	float total_wt = 0, total_tat = 0; 
	for (int i = 0 ; i < n ; i++) 
	{ 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
		printf("\n%10s\t%10.0f\t%10.0f\t%10.0f\t\t%10.0f", job[i].pid,  job[i].arrival_time, job[i].burst_time, wt[i], tat[i]);
	} 

	printf("\nAverage Waiting time    = %f", total_wt/n); 
	printf("\nAverage Turnaround time = %f\n\n", total_tat/n); 


    printf("GANTT CHART\n");

	printf("\n");
	for(int i=0;i<n;i++)
		printf("-----------------");
	printf("\n");

    for(int i=0;i<n;i++)	
		printf("|\t%-10s", job[i].pid);
    printf("|");

	printf("\n");
	for(int i=0;i<n;i++)
		printf("-----------------");
	printf("\n");

	printf("%-10.2f", 0.0);
    for(int i=0;i<n;i++)	
		printf("\t%-10.2f", tat[i]+job[i].arrival_time);

	printf("\n\n");
} 


void sjfp(int n, jobs job[n]) 
{ 
	float wt[n], tat[n], rt[n], total_wt = 0, total_tat = 0; 

	for (int i = 0; i < n; i++) 
		rt[i] = job[i].burst_time; 

	int complete = 0, t = 0, minm = MAX, shortest=0; 
	float finish_time; 
	int check = 0; 
	char pid[20][20];
	float time_order[20], time_done[20];
	strcpy(pid[0], "");
	time_order[0]=0;
	int pindex=0;
	

	while (complete != n) 
	{ 
		for (int j = 0; j < n; j++) 
		{ 
			if ((job[j].arrival_time <= t) && (rt[j] < minm) && rt[j] > 0) 
			{ 
				minm = rt[j]; 
				shortest = j; 
				check = 1; 
			} 
		} 

		if(strcmp(pid[pindex], job[shortest].pid) != 0)
		{
	
			pindex++;
			strcpy(pid[pindex], job[shortest].pid);

			time_order[pindex] += 1;
		}
		else
		{
			time_order[pindex] += 1;
		}

		if (check == 0) 
		{ 
			t++; 
			continue; 
		} 

		rt[shortest]--; 

		minm = rt[shortest]; 
		if (minm == 0) 
			minm = MAX; 

		if (rt[shortest] == 0) 
		{ 
			complete++; 
			check = 0; 

			finish_time = t + 1; 

			wt[shortest] = finish_time - job[shortest].burst_time - job[shortest].arrival_time; 


			if (wt[shortest] < 0) 
				wt[shortest] = 0; 
		} 


		t++; 
	}


	for (int i = 0; i < n; i++) 
		tat[i] = job[i].burst_time + wt[i]; 


	printf("\n%10s\t%10s\t%10s\t%10s\t%10s", "Process ID", "Arrival Time", "Burst Time", "Waiting Time", "Turnaround Time");
	for(int i=0; i<n; i++)
	{
		printf("\n%10s\t%10.0f\t%10.0f\t%10.0f\t\t%10.0f", job[i].pid, job[i].arrival_time, job[i].burst_time, wt[i], tat[i]);
	}

	for (int i = 0; i < n; i++) 
	{ 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
	} 

	printf("\nAverage Waiting time    = %f", total_wt/n ); 
	printf("\nAverage Turnaround time = %f\n", total_tat/n );

    printf("GANTT CHART\n");

	printf("\n");
	for(int i=0;i<pindex;i++)
		printf("-----------------");
	printf("\n");

    for(int i=1;i<=pindex;i++)	
		printf("|\t%-10s", pid[i]);
    printf("|");

	printf("\n");
	for(int i=0;i<pindex;i++)
		printf("-----------------");
	printf("\n");


    
	printf("\n");
	printf("%-10.2f", 0.0);

	float temptime=0;

    for(int i=1;i<=pindex;i++)	
	{
		printf("\t%-10.2f", time_order[i]+temptime);
		temptime+=time_order[i];	
	}
	printf("\n\n");


}


jobs create_job(char pid[20], float arrival_time, float burst_time)
{
	jobs job;
	strcpy(job.pid, pid);
	job.arrival_time = arrival_time;
	job.burst_time = burst_time;
	return job;
}


int main() 
{ 
/*
	int choice=0;
	int n;

	printf("\n\nChoose scheduling algorithm:\n\t1. FCFS\n\t2. SJF non pre-emptive\n\t3. SJF pre-emptive\n\t0. Exit\nEnter choice: ");
	scanf("%d",&choice);
	while(choice!=0)
	{
		printf("\nEnter number of processes: ");
		scanf("%d",&n);

		jobs job[n];

		for(int i=0;i<n;i++)
		{
			printf("\nEnter process ID   : ");
			scanf("%s", job[i].pid);
			printf("Enter arrival time : ");
			scanf("%f", &job[i].arrival_time);
			printf("Enter burst time   : ");
			scanf("%f", &job[i].burst_time);
		}

		if(choice==1)
			fcfs(n, job);
		else if(choice==2)
			sjfnp(n, job);
		else if(choice==3)
			sjfp(n, job);
		else
			printf("\nInvalid choice!");

	printf("\n\nChoose scheduling algorithm:\n\t1. FCFS\n\t2. SJF non pre-emptive\n\t3. SJF pre-emptive\n\t0. Exit\nEnter choice: ");
		scanf("%d",&choice);
	}
*/

	char *processes[] = {"p1","p2","p3","p4","p5"}; 
	int n = 5; 

	float burst_time[] = {6, 2, 3, 1, 2}; 
	float arrival_time[] = {0, 1, 1, 2, 2}; 

	jobs job[n];

	for(int i=0;i<n;i++)
	{
		job[i]=create_job(processes[i], arrival_time[i], burst_time[i]);
	}

	fcfs(n, job); 
	sjfnp(n, job); 
	sjfp(n, job);



	return 0; 
} 

