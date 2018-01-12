/**
  ******************************************************************************
  * @file    file_lock.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   �ļ�����ʾ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv) 
{
	if (argc > 1) 
	{
		int fd = open(argv[1], O_WRONLY);
		if(fd == -1) 
		{
			printf("Unable to open the file\n");
			exit(1);
		}
		static struct flock lock;

		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_whence = SEEK_SET;
		lock.l_len = 0;
		lock.l_pid = getpid();

		int ret = fcntl(fd, F_SETLKW, &lock);
		printf("Return value of fcntl:%d\n",ret);
		if(ret==0) 
		{
			while (1) 
			{
				scanf("%c", NULL);																																												
			}
		}
	}
}