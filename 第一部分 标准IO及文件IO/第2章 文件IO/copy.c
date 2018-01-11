/**
  ******************************************************************************
  * @file    copy.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   文件复制（使用文件IO）
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <fcntl.h>  
#include <sys/stat.h> 

/**宏定义***********************************************************************/ 
#define maxsize 256  


int main(int argc, char *argv[])  
{  
    int fd1,fd2;  
    int byte;  
    char buffer[maxsize];  
    if(argc != 3)  
    {  
		printf("command error!\n");  
		return -1;  
    }    
    if((fd1 = open(argv[1],O_RDONLY)) == -1)  
    {  
       	perror("open fails");  
		return -1;  
    }  
  //如果文件不存在，则创建，若存在，则覆盖；  
    if((fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC ,0664)) == -1)
    {  
		perror("open fails");  
		return -1;  
    }  
    while(1)  
    {  
		if((byte = read(fd1,buffer,maxsize)) > 0)  
		write(fd2,buffer,byte);  
       		if(byte == 0)  
            		break; //如果读不到数据，则返回  
    }  
    close(fd1);  
    close(fd2);  
    return 0;  
}  


