/**
  ******************************************************************************
  * @file    sem.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/sem.h>  
#define DELAY_TIME 3  
  
union semun   
{  
    int              val;    /* Value for SETVAL */  
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */  
    unsigned short  *array;  /* Array for GETALL, SETALL */  
    struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */  
};  
  
int init_sem(int sem_id,int init_value);  
int del_sem(int sem_id);  
int sem_p(int sem_id);  
int sem_v(int sem_id);  
  
int init_sem(int sem_id,int init_value)  
{  
    union semun sem_union;  
    sem_union.val = init_value;  
    if(semctl(sem_id, 0, SETVAL, sem_union) == -1)  
    {  
        perror("Initialize semaphore");  
        exit(-1);  
    }  
  
    return 0;  
}  
int del_sem(int sem_id)  
{  
    union semun sem_union;  
    if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)  
    {  
        perror("Delete semaphore");  
        return -1;  
    }  
}  
int sem_p(int sem_id)  
{  
    struct sembuf sem_b;  
    sem_b.sem_num = 0;  
    sem_b.sem_op = -1;  
    sem_b.sem_flg = SEM_UNDO;  
  
    if(semop(sem_id,&sem_b,1) == -1)  
    {  
        perror("P operation");  
        return -1;  
    }  
  
    return 0;  
}  
int sem_v(int sem_id)  
{  
    struct sembuf sem_b;  
    sem_b.sem_num = 0;  
    sem_b.sem_op = 1;  
    sem_b.sem_flg = SEM_UNDO;  
  
    if(semop(sem_id,&sem_b,1) == -1)  
    {  
        perror("V operation");  
        return -1;  
    }  
    return 0;  
}  
int main()  
{  
    pid_t pid;  
    int sem_id;  
  
    sem_id = semget(ftok(".",'a'), 1, 0666|IPC_CREAT);  
    init_sem(sem_id,0);  
  
    pid = fork();  
    if(pid < 0)  
    {  
        perror("fork fails");  
        exit(-1);  
    }  
    else if(pid == 0)  
    {  
        printf("Child process will wait for some seconds...\n");  
        sleep(DELAY_TIME);  
        printf("The returned value is %d in the child process(PID = %d)\n",  
                pid,getpid());  
        sem_v(sem_id);  
    }  
    else  
    {  
        sem_p(sem_id);  
        printf("The returned value is %d in the father process(PID = %d)\n",  
                pid,getpid());  
        sem_v(sem_id);  
        del_sem(sem_id);  
    }  
  
    return 0;  
}
