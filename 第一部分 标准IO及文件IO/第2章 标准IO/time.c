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
#define N 128 

/**
  * @brief     主函数
  * @param     argc
               argv
  * @retval    None
  */
int main(int argc, char *argv[])  
{  
    int n;  
    char buf[N];  
    FILE *fp;  
    time_t t;  
	char *t_buf = buf;
	
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
		t_buf = ctime(&t);
		printf("%s",t_buf);
        fprintf(fp,"%s",t_buf);  
        
		fflush(fp);  
        sleep(1);  
    }  
  
    fclose(fp);  
  
    return 0;  
}  


