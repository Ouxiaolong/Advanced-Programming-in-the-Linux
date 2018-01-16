/**
  ******************************************************************************
  * @file    mydaemon_control.c
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
#include<signal.h>
 
#define NORMAL 1
#defineROT13  2
 
intstyle;
 
intread_config(int etcfd, int *style)
{
    int len;
    char etcbuf[256];
 
    if((len = read(etcfd, etcbuf, 256)) <0)
	{
        syslog(LOG_ERR, "Error: read%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    etcbuf[len]='\0';
 
    // Determine style
    if( strncmp(etcbuf, "normal", 6)== 0)
	{
       *style = NORMAL;
        syslog(LOG_INFO, "output style isnormal\n");
    }else if( strncmp(etcbuf,"rot13", 5) == 0)
	{
        *style = ROT13;
        syslog(LOG_INFO, "output style isrot13\n");
    }
	else
	{
        syslog(LOG_ERR, "invalid output style\n");
        return(2);
    }
 
    return(0);
}
 
voidsig_act(int sig)
{
    if( sig == SIGUSR1)
	{
        style = NORMAL;
        syslog(LOG_INFO, "RecievedSIGUSR1, output style change to normal\n");
    }
	else if( sig == SIGUSR2)
	{
        style = ROT13;
        syslog(LOG_INFO, "ReceivedSIGUSR2, output style change to rot13\n");
    }
	else
	{
        style = 0;
    }
    return;
}
 
intmain(void)
{
    pid_t pid, sid;
    time_t timebuf;
    int   i, fd, etcfd, len;
    char  *buf;
 
    pid = fork();
    if(pid < 0)
	{
        syslog(LOG_ERR, "Error: fork%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
	else if(pid > 0)
	{   
		// Parent
        exit(EXIT_SUCCESS);
    }
 
    // Child
 
    // open log
    openlog("mydaemon", LOG_PID,LOG_DAEMON);
 
    // open config file
    if((etcfd =open("/etc/mydaemon.conf", O_RDONLY)) < 0)
	{
        syslog(LOG_ERR, "Error: open%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    // read config file
    if((len = read_config(etcfd, &style))< 0)
	{
        syslog(LOG_ERR, "Error: read%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    // close config file
    if(close(etcfd) < 0)
	{
        syslog(LOG_ERR, "Error: close%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
 
    // setsid
   if((sid = setsid()) < 0)
   {
        syslog(LOG_ERR, "Error: setsid%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
 
    // change work directory
    if((chdir("/")) < 0)
	{
        syslog(LOG_ERR, "Error: chdir%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
 
    // change umask
    umask(0);
 
    // close unnessary file descriptions
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
 
    // malloc buf
    len = strlen(ctime(&timebuf));
    buf = malloc(len+1);
 
    // register signal
    signal(SIGUSR1, sig_act);
    signal(SIGUSR2, sig_act);
 
    // main work, write current datetime tofile 10 second per
    while(1)
    {
        if((fd =open("/var/log/mydaemon.log", \
            O_CREAT | O_WRONLY | O_APPEND,0600)) < 0)
		{
            syslog(LOG_ERR, "Error: open%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
 
        time(&timebuf);
        bzero(buf, len+1);
        strncpy(buf,ctime(&timebuf),len+1);
 
        // if style is rot13, rotate character;normal style, keep unchanged
        if(style == ROT13)
		{
            for(i=0; i<=len; i++)
            {
                if(buf[i] >= 'A' &&buf[i] <= 'M' || buf[i] >= 'a' && buf[i] <= 'm')
				{
                    buf[i] +=13;
                }else if( buf[i] >= 'N'&& buf[i] <= 'Z' || buf[i] >= 'n' && buf[i] <= 'z')
				{
                    buf[i] -=13;
                }
            }
        }
		else
		{
            ;
        }
        write(fd, buf, len+1);
 
        close(fd);
 
        sleep(10);
    }
 
    free(buf);
 
    // close log
    closelog();
 
    exit(EXIT_SUCCESS);
}

