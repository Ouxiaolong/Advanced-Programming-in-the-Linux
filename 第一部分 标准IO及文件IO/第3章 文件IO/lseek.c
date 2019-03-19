/**
  ******************************************************************************
  * @file    lseek.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   文件定位
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/stat.h>  
#include <sys/types.h>  

/**
  * @brief     主函数
  * @param     argc
               argv
  * @retval    None
  */
int main(int argc, const char *argv[])  
{  
    int fd;  
    int length; 
	
    if(argc != 2)  
    {  
        printf("command error!\n");  
        return -1;  
    }  
    if((fd = open(argv[1],O_RDONLY)) == -1)  
    {  
        perror("open fails");  
        return -1;  
    }  
	
    length = lseek(fd,0,SEEK_END);  
    printf("The length of %s is %d bytes!\n",argv[1],length);  
  
    return 0;  
}  


