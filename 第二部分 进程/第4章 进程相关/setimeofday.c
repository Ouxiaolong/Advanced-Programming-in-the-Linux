/**
  ******************************************************************************
  * @file    setimeofday.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   setimeofday函数使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
int main(void)  
{  
    char t_string[] = "2012-04-28 22:30:00";  
    struct tm time_tm;  
    struct timeval time_tv;  
    time_t timep;  
    int ret = 0;  
  
    sscanf(t_string, "%d-%d-%d %d:%d:%d", &time_tm.tm_year, &time_tm.tm_mon, &time_tm.tm_mday, &time_tm.tm_hour, &time_tm.tm_min, &time_tm.tm_sec);  
    time_tm.tm_year -= 1900;  
    time_tm.tm_mon -= 1;  
    time_tm.tm_wday = 0;  
    time_tm.tm_yday = 0;  
    time_tm.tm_isdst = 0;  
  
    timep = mktime(&time_tm);  
    time_tv.tv_sec = timep;  
    time_tv.tv_usec = 0;  
  
    ret = settimeofday(&time_tv, NULL);  
    if(ret != 0)  
    {  
        fprintf(stderr, "settimeofday failed\n");  
        return -1;  
    }  
    return 0;  
}
