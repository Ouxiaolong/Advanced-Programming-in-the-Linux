/**
  ******************************************************************************
  * @file    read_fifo.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   read_fifo API
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <errno.h>  

#define BUFFER_SIZE 1024  
int main(int argc, const char *argv[])  
{  
    int fd;  
  
    if(argc < 2)  
    {  
        printf("Usage:%s <filename>\n",argv[0]);  
        return -1;  
    }  
  
    if((fd = open(argv[1],O_RDONLY)) < 0)  
    {  
        perror("open error");  
        exit(-1);  
    }  
    printf("open fifo %s for reading success!\n",argv[0]);  
    char buffer[BUFFER_SIZE];  
    ssize_t n;  
    while(1)  
    {  
        if((n = read(fd,buffer,BUFFER_SIZE)) == -1)  
        {  
            perror("read fails");  
            return -1;  
        }  
        else if(n == 0)  
        {  
            printf("peer close fifo\n");  
            break;  
        }  
        else  
        {  
            buffer[n] = '\0';  
            printf("read %d bytes from fifo:%s\n",n,buffer);  
        }  
    }  
    return 0;  
}
