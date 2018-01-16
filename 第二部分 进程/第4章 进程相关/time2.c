/**
  ******************************************************************************
  * @file    time2.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <time.h>  
#include<stdlib.h> 
 
int main(void)  
{  
    int i;  
    srand((unsigned) time(NULL));  
    printf("ten random numbers from 0 to 99:\n");  
  
    for(i = 0;i < 10;i++)  
    {  
        printf("%d\n",rand()%100);  
    }  
  
    return 0;  
} 
