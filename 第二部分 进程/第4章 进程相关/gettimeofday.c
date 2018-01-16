/**
  ******************************************************************************
  * @file    gettimeofday.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   gettimeofday函数使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <sys/time.h>
#include <time.h>
#include <stdio.h>

int main(void)  
{  
    char strtime[20] = {0};  
    time_t timep;  
    struct tm *p_tm;  
    timep = time(NULL);  
    p_tm = localtime(&timep);  
    strftime(strtime, sizeof(strtime), "%Y-%m-%d %H:%M:%S", p_tm);  
    return 0;  
}  

