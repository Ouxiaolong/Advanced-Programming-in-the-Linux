/**
  ******************************************************************************
  * @file    cp.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   文件复制（使用标准文件IO）
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
#include <fcntl.h>  

/**宏定义***********************************************************************/ 
#define maxsize 5  

/**
  * @brief     主函数
  * @param     argc
               argv
  * @retval    None
  */
int main(int argc, char *argv[])  
{  
    FILE *fp1 ,*fp2;  
    char buffer[maxsize];  
    char *p,*q;  
    if(argc < 3)  
    {  
        printf("Usage:%s <srcfile> <desfile>\n",argv[0]);  
        return -1;  
    }  
    if((fp1 = fopen(argv[1],"r")) == NULL)  
    {  
        perror("fopen argv[1] fails");  
        return -1;  
    }  
    if((fp2 = fopen(argv[2],"w+")) == NULL)  
    {  
        perror("fopen argv[2] fails");  
        return -1;  
    }  
    while((p = fgets(buffer,maxsize,fp1)) != NULL)  
    {  
         fputs(buffer,fp2);  
    }  
    if(p == NULL)  
    {  
        if(ferror(fp1))  
            perror("fgets failed");  
        if(feof(fp1))  
            printf("cp over!\n");  
    }  
    fclose(fp1);  
    fclose(fp2);  
    return 0;  
}  


