/**
  ******************************************************************************
  * @file    gmtime.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   gmtime函数使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>   
#include <time.h>   

int main(void)  
{  
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};  
    time_t timep;  
    struct tm *p_tm;  
	
    timep = time(NULL);  
    p_tm = gmtime(&timep); /*获取GMT时间*/  
	
    printf("%d-%d-%d ", (p_tm->tm_year+1900), (p_tm->tm_mon+1), p_tm->tm_mday);  
    printf("%s %d:%d:%d\n", wday[p_tm->tm_wday], p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);  
}  
