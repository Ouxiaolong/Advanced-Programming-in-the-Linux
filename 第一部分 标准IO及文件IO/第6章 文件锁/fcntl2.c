/**
  ******************************************************************************
  * @file    fcntl2.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   文件锁
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/**********************使能非阻塞I/O********************
*int flags;
*if(flags = fcntl(fd, F_GETFL, 0) < 0)
*{
*    perror("fcntl");
*    return -1;
*}
*flags |= O_NONBLOCK;
*if(fcntl(fd, F_SETFL, flags) < 0)
*{
*    perror("fcntl");
*    return -1;
*}
*******************************************************/

/**********************关闭非阻塞I/O******************
flags &= ~O_NONBLOCK;
if(fcntl(fd, F_SETFL, flags) < 0)
{
    perror("fcntl");
    return -1;
}
*******************************************************/

int main()
{
    char buf[10] = {0};
    int ret;
    int flags;
    
    //使用非阻塞io
    if(flags = fcntl(STDIN_FILENO, F_GETFL, 0) < 0)
    {
        perror("fcntl");
        return -1;
    }
    flags |= O_NONBLOCK;
    if(fcntl(STDIN_FILENO, F_SETFL, flags) < 0)
    {
        perror("fcntl");
        return -1;
    }

    while(1)
    {
        sleep(2);
        ret = read(STDIN_FILENO, buf, 9);
        if(ret == 0)
        {
            perror("read--no");
        }
        else
        {
            printf("read = %d\n", ret);
        }
        
        write(STDOUT_FILENO, buf, 10);
        memset(buf, 0, 10);
    }

    return 0;
}