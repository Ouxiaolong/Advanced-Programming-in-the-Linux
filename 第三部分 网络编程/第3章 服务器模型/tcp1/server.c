/**
  ******************************************************************************
  * @file    server.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   服务器端
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
#define BUFFER_SIZE 128  
#define PORT 8888  

int main()  
{  
    int listenfd, clientfd;  
    int n;  
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
        printf("listenfd:%d\n",listenfd);  
    }  
  
    memset(&serveraddr,0,sizeof(serveraddr));  
    serveraddr.sin_family = AF_INET;  
    serveraddr.sin_port = htons(PORT);  
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
    if(bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0) //绑定IP地址和端口号  
    {  
        perror("bind error");  
        exit(-1);  
    }  
    else  
    {  
        printf("bind successfully!\n");  
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
  
    peerlen = sizeof(clientaddr);  
    while(1)  
    {  
        if((clientfd = accept(listenfd,(struct sockaddr *)&clientaddr,&peerlen)) < 0) //循环等待客户端的连接  
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
        while(1)  
        {  
            if((n = recv(clientfd,buffer,BUFFER_SIZE,0)) == -1) //循环接收客户端发送的数据  
            {  
                perror("recv error");  
                exit(-1);  
            }  
            else if(n == 0) //此时，客户端断开连接  
            {  
                break;  
            }  
            else  
            {  
                printf("Received message:%s\n",buffer);  
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
        }  
        close(clientfd); //客户端断开连接后，服务端也断开  
    }  
    close(listenfd);  
  
    return 0;  
}  
