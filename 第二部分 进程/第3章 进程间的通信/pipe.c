/**
  ******************************************************************************
  * @file    pipe.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <unistd.h>  
#include <string.h>  
#include <stdlib.h>  

int pid,pid1,pid2;  
  
int main(int argc, const char *argv[])  
{  
    int fd[2];  
    char outpipe[100],inpipe[100];  
  
    if(pipe(fd) < 0)  
    {  
        perror("pipe error!");  
        return -1;  
    }  
    if((pid1 = fork()) < 0)  
    {  
        perror("fork pid1 error");  
        return -1;  
    }  
    else if(pid1 == 0)  
    {  
        printf("Child1's pid is %d\n",getpid());  
        close(fd[0]);  
        strcpy(outpipe,"Child 1 is sending a message!");  
        if(write(fd[1],outpipe,50) == -1)  
        {  
            perror("Child 1 write to outpipe error");  
            return -1;  
        }  
        exit(0);  
    }  
          
    if((pid2 = fork()) < 0)  
    {  
        perror("fork pid2 error");  
        return -1;  
    }  
    else if(pid2 == 0)  
    {  
        printf("Child2's pid is %d\n",getpid());  
        close(fd[0]);  
        strcpy(outpipe,"Child 2 is sending a message!");  
        sleep(1);  
        if(write(fd[1],outpipe,50) == -1)  
        {  
            perror("Child 2 write to outpipe error");  
            return -1;  
        }  
        exit(0);  
    }  
      
    close(fd[1]);  
    pid = wait(NULL);  
    printf("%d process is over!\n",pid);  
    if(read(fd[0],inpipe,50) == -1)  
    {  
        perror("read Child1 pipe error");  
        return -1;  
    }  
    printf("%s\n",inpipe);  
  
    pid = wait(NULL); //回收第二个结束的子进程  
    printf("%d process is over!\n",pid);  
    if(read(fd[0],inpipe,50) == -1)  
    {  
        perror("read Child1 pipe error");  
        return -1;  
    }  
    printf("%s\n",inpipe);  
  
    return 0;  
}  
