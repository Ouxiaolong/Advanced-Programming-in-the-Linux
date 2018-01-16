/**
  ******************************************************************************
  * @file    difftime.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   difftime函数使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <time.h>
#include <stdio.h>

int main(void)  
{  
    time_t timep1, timep2;  
    timep1 = time(NULL);  
    sleep(2);  
    timep2 = time(NULL);  
    printf("the difference is %f seconds\n", difftime(timep1, timep2));  
    return 0;  
}  
