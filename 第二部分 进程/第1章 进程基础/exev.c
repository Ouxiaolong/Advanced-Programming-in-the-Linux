/**
  ******************************************************************************
  * @file    exev.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   execlp 函数使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <unistd.h>  
  
int main()  
{  
	//调用execlp 函数，相当于调用了 "ps -ef"命令  
    if(execlp("ps","ps","-ef",NULL) < 0) //这里"ps"为filename "ps" 为argv[0] "-ef"为argv[1]，NULL为参数结束标志  
    {  
        perror("execlp error");  
        return -1;  
    }  
  
    return 0;  
}  
