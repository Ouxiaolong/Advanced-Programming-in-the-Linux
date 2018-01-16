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
#include <string.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/select.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#define PORT 8888  
#define MAXSIZE 128  
  
int main()  
{  
    int i,nbyte;  
    int listenfd, confd, maxfd;  
    char buffer[MAXSIZE];  
    fd_set global_rdfs, current_rdfs;  
    struct sockaddr_in addr,clientaddr;  
    int addrlen = sizeof(struct sockaddr_in);  
    int caddrlen = sizeof(struct sockaddr_in);  
  
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
    {  
        perror("socket error");  
        exit(-1);  
    }  
    else  
    {  
        printf("socket successfully!\n");  
        printf("listenfd : %d\n",listenfd);  
    }  
  
    memset(&addr, 0 ,addrlen);  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(PORT);  
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  
    if(bind(listenfd,(struct sockaddr *)&addr,addrlen) == -1)  
    {  
        perror("bind error");  
        exit(-1);  
    }  
    else  
    {  
        printf("bind successfully!\n");  
        printf("listen port:%d\n",PORT);  
    }  
  
    if(listen(listenfd,5) == -1)  
    {  
        perror("listen error");  
        exit(-1);  
    }  
    else  
    {  
        printf("listening...\n");  
    }  
  
    maxfd = listenfd;  
    FD_ZERO(&global_rdfs);  
    FD_SET(listenfd,&global_rdfs);  
  
    while(1)  
    {  
        current_rdfs = global_rdfs;  
        if(select(maxfd + 1,&current_rdfs, NULL, NULL,0) < 0)  
        {  
            perror("select error");  
            exit(-1);  
        }  
          
        for(i = 0; i <= listenfd + 1; i++)  
        {  
            if(FD_ISSET(i, &current_rdfs)) //fd 就绪  
            {  
                if(i == listenfd) //有新的连接  
                {  
                    if((confd = accept(listenfd,(struct sockaddr *)&clientaddr,&caddrlen)) == -1)  
                    {  
                        perror("accept error");  
                        exit(-1);  
                    }  
                    else  
                    {  
                        printf("Connect from [IP:%s PORT:%d]\n",  
                                inet_ntoa(clientaddr.sin_addr),clientaddr.sin_port);  
                        FD_SET(confd,&global_rdfs);  
                        maxfd = (maxfd > confd ? maxfd : confd);  
                    }  
                }  
                else  
                {  
                    if((nbyte = recv(i, buffer, sizeof(buffer),0)) < 0)  
                    {  
                        perror("recv error");  
                        exit(-1);  
                    }  
                    else if(nbyte == 0) //客户端close  
                    {  
                        close(i);  
                        FD_CLR(i,&global_rdfs); //将其清出  
                    }  
                    else  
                    {  
                        printf("recv:%s\n",buffer);  
                        send(i, buffer, sizeof(buffer),0);  
                    }  
                }  
            }  
        }  
    }  
    return 0;  
} 
