/**
  ******************************************************************************
  * @file    fork.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   创建进程
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/types.h>  
  
int global = 22;  
int main(void)  
{  
    int test = 0,stat;  
    pid_t pid;  
    pid = fork();  
    if(pid < 0)  
    {  
        perror("fork");  
        return -1;  
    }  
    else if(pid == 0)  
    {  
		global++;  
		test++;  
		printf("global = %d test = %d Child,my PID is %d\n",global,test,getpid());  
		exit(0);  
	}  
	else  
	{  
		global += 2;  
		test += 2;  
		printf("global = %d test = %d Parent,my PID is %d\n",global,test,getpid());  
        exit(0);  
    }  
}
