/**
  ******************************************************************************
  * @file    mydaemon.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<errno.h>
#include<syslog.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
 
int main(void)
{
    pid_t pid, sid;
    time_t timebuf;
    int   fd, len;
    char  *buf;
 
       // �����ӽ��̣�Ȼ�󸸽����˳�
    pid = fork();
    if(pid < 0)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
	else if(pid > 0)
	{ 
	// ������
        exit(EXIT_SUCCESS);
    }
 
    // �ӽ���
 
    // �����»Ự���½�����
    if((sid = setsid()) < 0)
	{
        perror("setsid");
        exit(EXIT_FAILURE);
    }
 
    // �ı䵱ǰ�Ĺ���Ŀ¼����Ŀ¼
    if((chdir("/")) < 0)
	{
        perror("chdir");
        exit(EXIT_FAILURE);
    }
 
    // �ı�Ŀ¼�ļ��Ĵ���ģʽ
    umask(0);
 
    // �رղ���Ҫ���ļ�������
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
 
    // malloc buf
    len = strlen(ctime(&timebuf));
    buf = malloc(len+1);
 
    // �ӽ�����Ҫ������ÿ10��������־�ļ�д�뵱ǰ��ʱ��
    while(1)
    {
        if((fd = open("/var/log/mydaemon.log",O_CREAT | O_WRONLY | O_APPEND,0600)) < 0)
		{
            perror("open file");
            exit(EXIT_FAILURE);
        }
 
        time(&timebuf);
        bzero(buf, len+1);
        strncpy(buf,ctime(&timebuf),len+1);
        write(fd, buf, len+1);
 
        close(fd);
 
        sleep(10);
    }
 
    free(buf);
 
    exit(EXIT_SUCCESS);
}
