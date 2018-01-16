/**
  ******************************************************************************
  * @file    mktime.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   mktime函数使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <time.h>
#include <stdio.h>

int main(void)  
{  
    time_t timep;
    struct tm *p_tm;  
    timep = time(NULL);  
	
    printf("time( ):%d\n", timep);  
    p_tm = localtime(&timep);  
    
	timep = mktime(p_tm);  
    printf("time( )->localtime( )->mktime( ):%d\n", timep);  
    return 0;  
} 
