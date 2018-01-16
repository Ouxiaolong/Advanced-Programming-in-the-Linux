/**
  ******************************************************************************
  * @file    client.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   客户端
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/socket.h>  
#include <sys/types.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#define BUFFER_SIZE 128  
#define PORT 8888  
  
int main()  
{  
    int n;  
    int serverfd, clientfd;  
    struct sockaddr_in serveraddr;  
    char buffer[BUFFER_SIZE];  
  
    if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
    {  
        perror("socket error");  
        exit(-1);  
    }  
    else  
    {  
        printf("clientfd:%d\n",clientfd);  
    }  
//设置服务端的IP地址和端口号  
    memset(&serveraddr,0,sizeof(serveraddr));  
    serveraddr.sin_family = AF_INET;  
    serveraddr.sin_port = htons(PORT);  
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
    if(connect(clientfd,(struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)  
    {  
        perror("connect error");  
        exit(-1);  
    }  
    else  
    {  
        printf("connect successfully!\n");  
    }  
  
    while(1)  
    {         
        printf("input > ");  
        fgets(buffer,sizeof(buffer),stdin);  
        if(strcmp(buffer,"quit\n") == 0) //遇到quit，退出  
            break;  
        buffer[strlen(buffer) - 1] = '\0'; //将'\n'去掉  
        if(send(clientfd,buffer,sizeof(buffer),0) == -1)  
        {  
            perror("send error");  
            exit(-1);  
        }  
        memset(buffer,0,sizeof(buffer)); //清空buffer  
        if((n = recv(clientfd,buffer,sizeof(buffer),0)) == -1)  
        {  
            perror("recv error");  
            exit(-1);  
        }  
        else if(n == 0)  
        {  
            break; //若服务端意外关闭  
        }  
        else  
        {  
            printf("echo:%s\n",buffer);  
        }  
    }  
    close(clientfd);  
  
    return 0;  
}
