/**
  ******************************************************************************
  * @file    print_err.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   输出错误
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <string.h>  
#include <stdio.h>  
#include <errno.h>  
#include <stdlib.h>  

int main(int argc, char *argv[])  
{  
	int idx = 0;  
	for (idx = 0; idx < sys_nerr; idx++)
	{  
		printf("Error #%3d: %s\n", idx, strerror(idx));  
    }  
	exit(0);  
}  


