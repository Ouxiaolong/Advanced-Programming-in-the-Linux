/**
  ******************************************************************************
  * @file    write_fifo.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   write_fifo API
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
    if((fd = open(argv[1],O_WRONLY)) < 0)  
    {  
        perror("open error");  
        exit(-1);  
    }  
    printf("open fifo %s for writing success!\n",argv[0]);  
    char buffer[BUFFER_SIZE];  
    ssize_t n;  
    while(fgets(buffer,BUFFER_SIZE,stdin))  
    {  
        if((n = write(fd,buffer,strlen(buffer))) == -1)  
        {  
            perror("write fails");  
            break;  
        }  
    }  
    return 0;  
} 
