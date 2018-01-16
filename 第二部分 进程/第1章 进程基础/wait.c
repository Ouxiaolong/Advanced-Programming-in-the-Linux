/**
  ******************************************************************************
  * @file    wait.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   wait函数的使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include<stdio.h>
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <stdlib.h>  
#include <unistd.h>  
         
int main(int argc, char **argv)  
{  
    pid_t pid;  
  
    printf("parent[pid=%d] is born\n", getpid());  
    if (-1 == (pid = fork())) 
	{  
        perror("fork error");  
        return -1;  
    }  
    if (pid == 0)
	{  
        printf("child[pid=%d] is born\n", getpid());  
        sleep(20);  
        printf("child is over\n");  
          
        exit(123); //return 123;   
    }  
    else
	{  
        pid_t pid_w;  
        int status;  
          
        printf("parent started to wait...\n");  
        pid_w = wait(&status);  
        printf("parent wait returned\n");  
          
        if (pid_w < 0) 
		{  
            perror("wait error");  
            return 1;  
        }  
          
        if (WIFEXITED(status))
		{   
            status = WEXITSTATUS(status);  
            printf("wait returns with pid = %d. return status is %d\n", pid_w, status);  
        } 
		else
		{  
            printf("wait returns with pid = %d. the child is terminated abnormally\n", pid_w);  
        }  
          
//      while(1);  
        printf("father is over\n");  
          
        return 0;  
    }  
}

