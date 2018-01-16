/**
  ******************************************************************************
  * @file    mydaemon_syslog.c
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
 
intmain(void)
{
    pid_t pid, sid;
    time_t timebuf;
    int   fd, len;
    char  *buf;
 
    pid = fork();
    if(pid < 0){
       syslog(LOG_ERR, "Error: fork %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }else if(pid > 0){  // Parent
        exit(EXIT_SUCCESS);
    }
 
    // Child
 
    // open log
    openlog("mydaemon", LOG_PID,LOG_DAEMON);
 
    // setsid
    if((sid = setsid()) < 0){
        syslog(LOG_ERR, "Error: setsid%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
 
    // change work directory
    if((chdir("/")) < 0){
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
 
    // main work, write current datetime tofile 10 second per
    while(1)
    {
        if((fd =open("/var/log/mydaemon.log", \
            O_CREAT | O_WRONLY | O_APPEND,0600)) < 0){
            syslog(LOG_ERR, "Error: open%s\n", strerror(errno));
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
 
    // close log
    closelog();
 
    exit(EXIT_SUCCESS);
}
