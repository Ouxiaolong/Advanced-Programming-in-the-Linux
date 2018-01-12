/**
  ******************************************************************************
  * @file    fcntl.c
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    //��׷�ӵ���ʽ���ļ�
    int fd = fd = open("test.txt", O_TRUNC | O_RDWR | O_APPEND | O_CREAT, 0777);
    if(fd < 0)
    {
        perror("open");
        return -1;
    }
    printf("fd = %d\n", fd);
    
    fcntl(fd, F_SETFD, 0);//�ر�fd��close-on-exec��־

    write(fd, "hello c program\n", strlen("hello c program!\n"));

    pid = fork();
    if(pid < 0)
    {
            perror("fork");
            return -1;
    }
    if(pid == 0)
    {
        printf("fd = %d\n", fd);
        
        int ret = execl("./main", "./main", (char *)&fd, NULL);
        if(ret < 0)
        {
            perror("execl");
            exit(-1);
        }
        exit(0);
    }

    wait(NULL);

    write(fd, "hello c++ program!\n", strlen("hello c++ program!\n"));

    close(fd);

    return 0;
}