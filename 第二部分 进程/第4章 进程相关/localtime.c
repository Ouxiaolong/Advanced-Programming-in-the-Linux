/**
  ******************************************************************************
  * @file    localtime.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   localtime函数使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <time.h>   
#include <stdio.h>   
  
int main()  
{  
    time_t timer;  
    struct tm *tblock;  
    timer = time(NULL);  
    tblock = localtime(&timer);  
  
    printf("Local time is: %s",asctime(tblock));  
      
    return 0;   
} 
