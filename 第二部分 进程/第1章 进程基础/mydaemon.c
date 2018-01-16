/**
  ******************************************************************************
  * @file    mydaemon.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<errno.h>
#include<syslog.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
 
int main(void)
{
    pid_t pid, sid;
    time_t timebuf;
    int   fd, len;
    char  *buf;
 
       // 创建子进程，然后父进程退出
    pid = fork();
    if(pid < 0)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
	else if(pid > 0)
	{ 
	// 父进程
        exit(EXIT_SUCCESS);
    }
 
    // 子进程
 
    // 创建新会话和新进程组
    if((sid = setsid()) < 0)
	{
        perror("setsid");
        exit(EXIT_FAILURE);
    }
 
    // 改变当前的工作目录到根目录
    if((chdir("/")) < 0)
	{
        perror("chdir");
        exit(EXIT_FAILURE);
    }
 
    // 改变目录文件的创建模式
    umask(0);
 
    // 关闭不必要的文件描述符
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
 
    // malloc buf
    len = strlen(ctime(&timebuf));
    buf = malloc(len+1);
 
    // 子进程主要工作，每10秒钟向日志文件写入当前的时间
    while(1)
    {
        if((fd = open("/var/log/mydaemon.log",O_CREAT | O_WRONLY | O_APPEND,0600)) < 0)
		{
            perror("open file");
            exit(EXIT_FAILURE);
        }
 
        time(&timebuf);
        bzero(buf, len+1);
        strncpy(buf,ctime(&timebuf),len+1);
        write(fd, buf, len+1);
 
        close(fd);
 
        sleep(10);
    }
 
    free(buf);
 
    exit(EXIT_SUCCESS);
}
