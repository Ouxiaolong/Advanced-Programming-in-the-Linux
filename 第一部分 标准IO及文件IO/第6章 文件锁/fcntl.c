/**
  ******************************************************************************
  * @file    fcntl.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   文件锁-使用F_GETFL和F_SETFL这两种fcntl 命令
  *                 改变STDIN_FILENO的属性上O_NONBLOCK 选项,实现非阻塞读终端的功能
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define    MSG_TRY "try again\n"

int main(void)
{
	char buf[10];
	int n;
	int flags;
	
	flags = fcntl(STDIN_FILENO, F_GETFL);
	flags |= O_NONBLOCK;
	
	if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1)
	{
		perror("fcntl");
		exit(1);
	}
	tryagain:
	n = read(STDIN_FILENO, buf, 10);
	if (n < 0) 
	{
		if (errno == EAGAIN)
		{
			sleep(1);
			write(STDOUT_FILENO, MSG_TRY,strlen(MSG_TRY));
goto tryagain;
		}
		perror("read stdin");
		exit(1);
	}
	write(STDOUT_FILENO, buf, n);
	return 0;
}
