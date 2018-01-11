/**
  ******************************************************************************
  * @file    time.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   时间
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <unistd.h>  
#include <time.h>  

/**宏定义***********************************************************************/ 
#define N 64  
 
int main(int argc, char *argv[])  
{  
    int n;  
    char buf[N];  
    FILE *fp;  
    time_t t;  
  
    if(argc < 2)  
    {  
        printf("Usage : %s <file >\n",argv[0]);  
        return -1;  
    }  
  
    if((fp = fopen(argv[1],"a+")) == NULL)  
    {  
        perror("open fails");  
        return -1;  
    }  
  
    while(1)  
    {  
        time(&t);  
        fprintf(fp,"%s",ctime(&t));  
        fflush(fp);  
        sleep(1);  
    }  
  
    fclose(fp);  
  
    return 0;  
}  


