#include<pthread.h> 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int arr[20];
int max, min, len;
float avg;

void *calcAvg(void *param)
{
	avg = 0;
	for(int i = 0; i < len; i++)
		avg += arr[i];

	avg = avg/len;
	pthread_exit(0); 
} 

void *getMax(void *param)
{ 
	max = arr[0];
	for(int i = 1; i < len; i++)
		if(max < arr[i]) 
			max = arr[i];
	
	pthread_exit(0);
}

void *getMin(void *param)
{ 
	min = arr[0];
	for(int i = 1; i < len; i++)
		if(min > arr[i]) 
			min = arr[i];
	
	pthread_exit(0);
} 

void main(int argc, char *argv[]) 
{ 
	pthread_t tid1, tid2, tid3;
	pthread_attr_t attr1, attr2, attr3;

	if (argc < 2) 
	{ 
		fprintf(stderr,"\nUsage: Enter list of integer values\n"); 
		return; 
	}

	for(int i = 1; i < argc; i++) 
		arr[i-1] = atoi(argv[i]);

	len=argc-1;

	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_attr_init(&attr3); 

	pthread_create(&tid3, &attr1, calcAvg, arr);
	pthread_create(&tid1, &attr2, getMax, arr);
	pthread_create(&tid2, &attr3, getMin, arr);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL); 

	printf("\nThe average value is %f", avg);
	printf("\nThe maximum value is %d", max);
	printf("\nThe minimum value is %d", min);
	printf("\n");
} 

