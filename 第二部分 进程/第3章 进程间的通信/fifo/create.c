/**
  ******************************************************************************
  * @file    create.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/stat.h>  
#include <string.h>  
#include <errno.h>  

int main(int argc,char *argv[])  
{  
    if(argc < 2)  
    {  
        printf("Usage:%s <filename>\n",argv[0]);  
        return -1;  
    }  
	
    if(mkfifo(argv[1],0664) < 0)  
    {  
        perror("mkfifo fails");  
        exit(-1);  
    }  
    return 0;  
}
