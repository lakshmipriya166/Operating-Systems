#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//For semaphore operations - sem_init, sem_wait, sem_post
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/types.h>
#include<unistd.h>
extern int errno;
#define SIZE 10 /* size of the shared buffer */
#define VARSIZE 1 /* size of shared variable = 1 byte */
#define INPUTSIZE 20
#define SHMPERM 0666 /* shared memory permissions */
int segid; /* ID for shared memory buffer */
int empty_id;
int full_id;
int mutex_id;
char *buff;
char *input_string;
sem_t *empty;
sem_t *full;
sem_t *mutex;
int p = 0, c = 0;
int main()
{
    int i = 0;
    pid_t temp_pid;
    segid = shmget (100, SIZE, IPC_EXCL | SHMPERM );
    empty_id = shmget(101, sizeof(sem_t), IPC_EXCL | SHMPERM);
    full_id = shmget(102, sizeof(sem_t), IPC_EXCL | SHMPERM);
    mutex_id=shmget(103, sizeof(sem_t), IPC_EXCL | SHMPERM);
    buff = shmat(segid, (char *)0, 0);
    empty = shmat(empty_id, (char *)0, 0);
    full = shmat(full_id, (char *)0, 0);
    mutex = shmat(mutex_id, (char *)0, 0);
    printf("\nConsumer Process Started\n");
    while (i < 10)
    {
        printf("\nConsumer %d trying to acquire Semaphore Full\n", getpid());
        sem_wait(full);
        printf("\nConsumer %d successfully acquired Semaphore Full\n", getpid());
        printf("\nConsumer %d trying to acquire Semaphore Mutex\n", getpid());
        sem_wait(mutex);
        printf("\nConsumer %d successfully acquired Semaphore Mutex\n", getpid());
        printf("\nConsumer %d Consumed Item [%c]\n", getpid(), buff[c]);
        buff[c]=' ';
        c++;
        printf("\nItems consumed: %d\n", i+1);
        i++;
        sem_post(mutex);
        printf("\nConsumer %d released Semaphore Mutex\n", getpid());
        sem_post(empty);
        printf("\nConsumer %d released Semaphore Empty\n", getpid());
        sleep(1);
    }
    shmdt(buff);
    shmdt(empty);
    shmdt(full);
    shmdt(mutex);
    shmctl(segid, IPC_RMID, NULL);
    semctl(empty_id, 0, IPC_RMID, NULL);
    semctl(full_id, 0, IPC_RMID, NULL);
    semctl(mutex_id, 0, IPC_RMID, NULL);
    sem_destroy(empty);
    sem_destroy(full);
    sem_destroy(mutex);
    printf("\nConsumer Process Ended\n");
    return(0);
}

