/**
  ******************************************************************************
  * @file    ctime.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   ctime使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>   
#include <time.h>   
int main()   
{  
    time_t t;  
    time(&t);  
      
    printf("Today's date and time: %s",ctime(&t));  
    return 0;   
}
