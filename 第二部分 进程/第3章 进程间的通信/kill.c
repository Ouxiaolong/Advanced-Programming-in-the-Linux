/**
  ******************************************************************************
  * @file    kill.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <signal.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <unistd.h>  
  
int main(int argc, char *argv[])  
{  
    pid_t pid;  
    int ret;  
  
    if((pid = fork()) < 0)  
    {  
        perror("fork error");  
        exit(-1);  
    }  
    if(pid == 0)  
    {  
        printf("child(pid : %d)is waiting for any signal\n",getpid());  
        raise(SIGSTOP);  
        exit(0);  
    }  
    sleep(1);  
    if((waitpid(pid,NULL,WNOHANG)) == 0)  
    {  
        kill(pid,SIGKILL);  
        printf("parent kill child process %d\n",pid);     
    }  
    waitpid(pid,NULL,0);  
    return 0;  
}
