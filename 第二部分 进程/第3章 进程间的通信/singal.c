/**
  ******************************************************************************
  * @file    singal.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <signal.h>  
#include <sys/types.h>  

pid_t pid;  

void driver_handler(int signo);  
void saler_handler(int signo);  
  
int main(int argc,char *argv[])  
{  
    if((pid = fork()) < 0)  
    {  
        perror("fork error");  
        return -1;  
    }  
    if(pid > 0)  
    {  
        signal(SIGTSTP,driver_handler);  
        signal(SIGINT,SIG_IGN);  
        signal(SIGQUIT,SIG_IGN);  
        signal(SIGUSR1,driver_handler);  
        signal(SIGUSR2,driver_handler);  
        while(1)  
            pause();  
    }  
    if(pid == 0)  
    {  
        signal(SIGINT,saler_handler);  
        signal(SIGTSTP,SIG_IGN);  
        signal(SIGQUIT,saler_handler);  
        signal(SIGUSR1,saler_handler);  
        signal(SIGUSR2,SIG_IGN);  
        while(1)  
            pause();  
    }  
    return 0;  
}  
void driver_handler(int signo)  
{  
    if(signo == SIGUSR1)  
        printf("Let's gogogo!\n");  
    if(signo == SIGUSR2)  
        printf("Stop the bus!\n");  
    if(signo == SIGTSTP)  
        kill(pid,SIGUSR1);  
} 
 
void saler_handler(int signo)  
{  
    pid_t ppid = getppid();  
    if(signo == SIGINT)  
        kill(ppid,SIGUSR1);  
    if(signo == SIGQUIT)  
        kill(ppid,SIGUSR2);  
    if(signo == SIGUSR1)  
    {  
        printf("please get off the bus\n");  
        kill(ppid,SIGKILL);  
        exit(0);  
    }  
} 
