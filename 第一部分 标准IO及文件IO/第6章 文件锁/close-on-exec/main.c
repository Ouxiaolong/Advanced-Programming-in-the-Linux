/**
  ******************************************************************************
  * @file    main.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int fd = (int)(*argv[1]);//描述符
    
    printf("fd = %d\n", fd);

    int ret = write(fd, "hello linux\n", strlen("hello linux\n"));
    if(ret < 0)
    {
        perror("write");
        return -1;
    }

    close(fd);

    return 0;
}