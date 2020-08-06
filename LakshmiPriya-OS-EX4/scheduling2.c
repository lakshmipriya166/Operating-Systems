#include <stdio.h>
#include <string.h>
#define MAX 999999999

typedef struct 
{
	char pid[20];
	float arrival_time;
	float burst_time;
	int priority;
}jobs;


jobs create_job(char pid[20], float arrival_time, float burst_time, int priority)
{
	jobs job;
	strcpy(job.pid, pid);
	job.arrival_time = arrival_time;
	job.burst_time = burst_time;
	job.priority = priority;
	return job;
}


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


void prioritynp(int n, jobs job[n]) 
{ 
	float wt[n], tat[n]; 

	float time=0;
	int flag=0;
	jobs temp;
	char pid[20][20];
	float time_order[20];
	int pindex=0;

	atSort(n, job);

	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			
			if(job[i].priority > job[j].priority && job[j].arrival_time <= time)
			{
				temp = job[i];
				job[i] = job[j];
				job[j] = temp;
			}
		}


		strcpy(pid[pindex], job[i].pid);
		time_order[pindex] = job[i].burst_time;
		pindex++;

		time += job[i].burst_time;
		
		if(job[i+1].arrival_time > time)
			time += job[i+1].arrival_time;
	}

	strcpy(pid[pindex], job[i].pid);
	time_order[pindex] = job[i].burst_time;
	pindex++;


	findWaitingTime(n, job, wt); 

	findTurnAroundTime(n, job, wt, tat); 

	printf("\n%10s\t%10s\t%10s\t%10s\t%10s\t%10s", "Process ID", "Arrival Time", "Burst Time", "Priority", "Waiting Time", "Turnaround Time");
		
	float total_wt = 0, total_tat = 0; 
	for (i = 0 ; i < n ; i++) 
	{ 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
		printf("\n%10s\t%10.0f\t%10.0f\t%10d\t%10.0f\t\t%10.0f", job[i].pid,  job[i].arrival_time, job[i].burst_time, job[i].priority, wt[i], tat[i]);
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

	float temptime=0;

	for(i=0;i<pindex;i++)	
	{
		printf("\t%-10.2f", time_order[i]+temptime);
		temptime+=time_order[i];	
	}
	printf("\n\n");

}

void priorityp(int n, jobs job[n]) 
{ 
	float wt[n], tat[n], rt[n], total_wt = 0, total_tat = 0; 

	for (int i = 0; i < n; i++) 
		rt[i] = job[i].burst_time; 

	int complete = 0, t = 0, minm = MAX, prior=0; 
	float finish_time; 
	int check = 0; 
	char pid[20][20];
	float time_order[20];
	strcpy(pid[0], "");
	int pindex=0;

	for(int i=0;i<20;i++)
		time_order[i]=0;

	while (complete != n) 
	{ 
		for (int j = 0; j < n; j++) 
		{ 
			if ((job[j].arrival_time <= t) && (job[j].priority < minm) && rt[j] > 0) 
			{ 
				minm = job[j].priority; 
				prior = j; 
				check = 1; 
			} 
		} 

		if(strcmp(pid[pindex], job[prior].pid) != 0)
		{
	
			pindex++;
			strcpy(pid[pindex], job[prior].pid);

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

		rt[prior]--; 

		minm = rt[prior]; 
		if (minm == 0) 
			minm = MAX; 

		if (rt[prior] == 0) 
		{ 
			complete++; 
			check = 0; 

			finish_time = t + 1; 

			wt[prior] = finish_time - job[prior].burst_time - job[prior].arrival_time; 


			if (wt[prior] < 0) 
				wt[prior] = 0; 
		} 


		t++; 
	}


	for (int i = 0; i < n; i++) 
		tat[i] = job[i].burst_time + wt[i]; 


	printf("\n%10s\t%10s\t%10s\t%10s\t%10s\t%10s", "Process ID", "Arrival Time", "Burst Time", "Priority", "Waiting Time", "Turnaround Time");
	for(int i=0; i<n; i++)
	{
		printf("\n%10s\t%10.0f\t%10.0f\t%10d\t%10.0f\t\t%10.0f", job[i].pid,  job[i].arrival_time, job[i].burst_time, job[i].priority, wt[i], tat[i]);
	}

	for (int i = 0; i < n; i++) 
	{ 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
	} 

	printf("\nAverage Waiting time    = %f", total_wt/n ); 
	printf("\nAverage Turnaround time = %f\n", total_tat/n );

	printf("\nGANTT CHART\n");

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

	printf("%-10.2f", 0.0);

	float temptime=0;

    for(int i=1;i<=pindex;i++)	
	{
		printf("\t%-10.2f", time_order[i]+temptime);
		temptime+=time_order[i];	
	}
	printf("\n\n");


}


void rr(int n, jobs job[n])
{
	float wt[n], tat[n], rt[n], total_wt = 0, total_tat = 0; 
	float time, timeslice;
	int flag=0, remain=n, count, pindex=0;
	char pid[20][20];
	float time_order[20];
	strcpy(pid[0], "");
	time_order[0]=0;

	atSort(n, job);

	do
	{
		printf("\nEnter time slice: ");
		scanf("%f", &timeslice);
	}while(timeslice <= 0);

	for (int i = 0; i < n; i++) 
		rt[i] = job[i].burst_time; 
	
	printf("\n%10s\t%10s\t%10s\t%10s\t%10s", "Process ID", "Arrival Time", "Burst Time", "Waiting Time", "Turnaround Time");

	for(time=0,count=0;remain!=0;) 
	{ 
		if(rt[count]<=timeslice && rt[count]>0) 
		{ 	
			time+=rt[count]; 

			pindex++;
			strcpy(pid[pindex], job[count].pid);
			time_order[pindex]=rt[count];

			rt[count]=0; 
			flag=1; 

		} 
		else if(rt[count]>0) 
		{ 
			rt[count]-=timeslice; 
			time+=timeslice; 

			pindex++;
			strcpy(pid[pindex], job[count].pid);
			time_order[pindex]=timeslice;

		} 
		if(rt[count]==0 && flag==1) 
		{ 
			remain--; 
			printf("\n%10s\t%10.0f\t%10.0f\t%10.0f\t\t%10.0f", job[count].pid, job[count].arrival_time, job[count].burst_time, time-job[count].arrival_time-job[count].burst_time, time-job[count].arrival_time); 

			total_wt+=time-job[count].arrival_time-job[count].burst_time; 
			total_tat+=time-job[count].arrival_time; 
			flag=0; 
		} 
		if(count==n-1) 
			count=0; 
		else if(job[count+1].arrival_time<=time) 
			count++; 
		else 
			count=0; 
	} 

	printf("\nAverage Waiting Time    = %f", total_wt/n); 
	printf("\nAverage Turnaround Time = %f\n", total_tat/n); 
  
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

	printf("%-10.2f", 0.0);

	float temptime=0;

    for(int i=1;i<=pindex;i++)	
	{
		printf("\t%-10.2f", time_order[i]+temptime);
		temptime+=time_order[i];	
	}
	printf("\n\n");

}


int main() 
{ 
/*
	int choice=0;
	int n;

	printf("\n\nChoose scheduling algorithm:\n\t1. Round Robin\n\t2. Non pre-emptive priority\n\t3. Pre-emptive priority\n\t0. Exit\nEnter choice: ");
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
			if(choice!=1)
			{
				printf("Enter priority     : ");
				scanf("%d", &job[i].priority);
			}
		}

		if(choice==1)
			rr(n, job);
		else if(choice==2)
			prioritynp(n, job);
		else if(choice==3)
			priorityp(n, job);
		else
			printf("\nInvalid choice!");

		printf("\n\nChoose scheduling algorithm:\n\t1. Round Robin\n\t2. Non pre-emptive priority\n\t3. Pre-emptive priority\n\t0. Exit\nEnter choice: ");
		scanf("%d",&choice);
	}

*/
	char *processes[] = {"p1","p2","p3","p4","p5"}; 
	int n = 5; 

	float burst_time[] = {6, 2, 3, 1, 2}; 
	float arrival_time[] = {0, 1, 1, 2, 2}; 
	int prior[] = {2, 2, 4, 1, 3}; 

	jobs job[n];

	for(int i=0;i<n;i++)
	{
		job[i]=create_job(processes[i], arrival_time[i], burst_time[i], prior[i]);
	}

	printf("\n\nRoundrobin Scheduling\n");
	rr(n, job);

	printf("\n\nNon-preemptive Priority Scheduling\n");
	prioritynp(n, job);

	printf("\n\nPreemptive Priority Scheduling\n");
	priorityp(n, job);

	return 0; 
} 






