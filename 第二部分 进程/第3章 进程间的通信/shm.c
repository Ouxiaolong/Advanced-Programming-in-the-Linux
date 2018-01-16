/**
  ******************************************************************************
  * @file    shm.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/shm.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#define BUFFER_SIZE 2048  
  
int main()  
{  
    pid_t pid;  
    int shmid;  
    char *shm_addr;  
    char flag[] = "WROTE";  
    char buffer[BUFFER_SIZE];  
  
    if((shmid = shmget(IPC_PRIVATE,BUFFER_SIZE,0666)) < 0)  
    {  
        perror("shmget");  
        exit(-1);  
    }  
    else  
    {  
        printf("Create shared-memory:%d\n",shmid);  
    }  
  
    system("ipcs -m");  
    pid = fork();  
    if(pid < 0)  
    {  
        perror("fork error");  
        exit(-1);  
    }  
    else if(pid == 0)  
    {  
        shm_addr = shmat(shmid,0,0);  
        if(shm_addr == (void *)-1)  
        {  
            perror("Child:shmat");  
            exit(-1);  
        }  
        else  
        {  
            printf("Child:Attach shared-memory:%p \n",shm_addr);  
        }  
  
        system("ipcs -m");  
  
        while(strncmp(shm_addr,flag,strlen(flag)))  
        {  
            printf("Child:wait for enable data...\n");  
            sleep(5);  
        }  
  
        strcpy(buffer,shm_addr + strlen(flag));  
        printf("Child:shared-memory:%s\n",buffer);  
  
        if((shmdt(shm_addr)) < 0)  
        {  
            perror("shmdt");  
            exit(-1);  
        }  
        else  
        {  
            printf("Child: Deattach shared-memory\n");  
        }  
        system("ipcs -m");  
  
        if(shmctl(shmid,IPC_RMID,NULL) == -1)  
        {  
            perror("Child:shmctl(IPC_RMID)");  
            exit(-1);  
        }  
        else  
        {  
            printf("Delete shmared-memory\n");  
        }  
  
        system("ipcs -m");  
    }  
    else  
    {  
        if((shm_addr = shmat(shmid,0,0)) == (void *)-1)  
        {  
            perror("parent:shmat");  
            exit(-1);  
        }  
        else  
        {  
            printf("Parent:Attach shmared-memory:%p\n",shm_addr);  
        }  
  
        sleep(1);  
        printf("\nInput some string:\n");  
        fgets(buffer,BUFFER_SIZE,stdin);  
        strncpy(shm_addr + strlen(flag),buffer,strlen(buffer));  
        strncpy(shm_addr,flag,strlen(flag));  
  
        if((shmdt(shm_addr)) < 0)  
        {  
            perror("Parent:shmdt");  
            exit(-1);  
        }  
        else  
        {  
            printf("Parent : Deattach shared-memory\n");  
        }  
  
        system("ipcs -m");  
        waitpid(pid,NULL,0);  
        printf("Finsihed\n");  
    }  
      
    return 0;  
} 
