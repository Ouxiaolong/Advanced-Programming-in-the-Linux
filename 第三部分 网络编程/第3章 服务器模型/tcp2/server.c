/**
  ******************************************************************************
  * @file    server.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   服务器
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <signal.h>  
#define BUFFER_SIZE 128  
#define PORT 8888  
#define IP "192.168.3.51"  
  
void handler(int signo);  
  
int main()  
{  
    int listenfd, clientfd;  
    int n;  
    pid_t pid;  
    struct sockaddr_in serveraddr,clientaddr;  
    socklen_t peerlen;  
    char buffer[BUFFER_SIZE];  
  
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
    {  
        perror("socket error");  
        exit(-1);  
    }  
    else  
    {  
        printf("Socket successfully!\nlistenfd:%d\n",listenfd);  
    }  
  
    memset(&serveraddr,0,sizeof(serveraddr));  
    serveraddr.sin_family = AF_INET;  
    serveraddr.sin_port = htons(PORT);  
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
    if(bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)  
    {  
        perror("bind error");  
        exit(-1);  
    }  
    else  
    {  
        printf("bind successfully!\n");  
        printf("local IP:%s port:%d\n",IP,PORT);  
    }  
  
    if(listen(listenfd,10) == -1)  
    {  
        perror("listen error");  
        exit(-1);  
    }  
    else  
    {  
        printf("listening....\n");  
    }  
  
    signal(SIGCHLD,handler);//捕捉SIGCHLD信号，子进程死亡后，调用handler回收      
    peerlen = sizeof(clientaddr);  
    while(1)  
    {  
        if((clientfd = accept(listenfd,(struct sockaddr *)&clientaddr,&peerlen)) < 0)  
        {  
            perror("accept error");  
            exit(-1);  
        }  
        else  
        {  
            printf("connection from [%s:%d]\n",inet_ntoa(clientaddr.sin_addr)  
                    ,ntohs(clientaddr.sin_port));     
        }  
  
        memset(buffer,0,sizeof(buffer));  
        if((pid = fork()) < 0)  
        {  
            perror("fork error");  
            exit(-1);  
        }  
        else if(pid == 0)  
        {  
            close(listenfd);  
            while(1)  
            {  
                if((n = recv(clientfd,buffer,BUFFER_SIZE,0)) == -1)  
                {  
                    perror("recv error");  
                    exit(-1);  
                }  
                else if(n == 0)  
                {  
                    break;  
                }  
                else  
                {  
                    printf("Received message:%s\n",buffer);  
                }  
              
                if(send(clientfd, buffer, n, 0) == -1)  
                {  
                    perror("send error");  
                    exit(-1);  
                }  
                else  
                {  
                    printf("sendmessage:%s\n",buffer);  
                }  
            }  
            printf("client is closed\n");  
            exit(0);  
        }  
        else  
        {  
            close(clientfd);  
        }  
    }  
    close(listenfd);  
  
    return 0;  
}  
//接收到SIFCHLD信号后，回收子进程  
void handler(int signo)  
{  
    pid_t pid;  
    while((pid = waitpid(-1, NULL, WNOHANG)) > 0)  
    {  
        printf("child(%d) is over!\n",pid);  
    }  
} 
