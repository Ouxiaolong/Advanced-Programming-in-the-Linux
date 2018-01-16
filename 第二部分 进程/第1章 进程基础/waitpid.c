/**
  ******************************************************************************
  * @file    waitpid.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   waitpid函数使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <unistd.h>  
#include <stdlib.h>  
  
int main()  
{  
    pid_t pc, pr;  
  
    pc = fork();  
    if(pc < 0) /* 如果fork出错 */  
        printf("Error occured on forking\n");  
    else if(pc == 0) /* 如果是子进程 */  
    {  
        sleep(10); /* 睡眠10秒 */  
        exit(0);  
    }  
    /* 如果是父进程 */  
    do{  
        pr = waitpid(pc, NULL, WNOHANG); /* 使用了WNOHANG参数，waitpid不会在这里等待 */  
        if(pr == 0) /* 如果没有收集到子进程 */  
        {  
            printf("No child exited\n");  
            sleep(1);  
        }  
    }while(pr == 0); /* 没有收集到子进程，就回去继续尝试 */  
  
    if(pr == pc)  
        printf("successfully get child %d\n", pr);  
    else  
        printf("some error occured\n");  
}  


