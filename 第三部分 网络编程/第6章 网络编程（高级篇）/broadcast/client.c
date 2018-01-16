/**
  ******************************************************************************
  * @file    client.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#define N 64  
#define PORT 8888  
  
int main()  
{  
    int sockfd;  
    char buf[N];  
    struct sockaddr_in seraddr;  
    socklen_t peerlen = sizeof(seraddr);  
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  
    {  
        perror("socket error");  
        exit(-1);  
    }  
    else  
    {  
        printf("socket successfully!\n");  
        printf("sockfd:%d\n",sockfd);  
    }  
    memset(&seraddr, 0, sizeof(seraddr));  
    seraddr.sin_family = AF_INET;  
    seraddr.sin_port = htons(PORT);  
    seraddr.sin_addr.s_addr = inet_addr("192.168.0.110"); //接收方绑定广播地址  
    if(bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) == -1)  
    {  
        perror("bind error");  
        exit(-1);  
    }  
    else  
    {  
        printf("bind successfully!\n");  
        printf("PORT:%d\n",PORT);  
    }  
    while(1)  
    {  
        if(recvfrom(sockfd, buf, N, 0, (struct sockaddr *)&seraddr, &peerlen) < 0)  
        {  
            perror("fail to recvfrom");  
            exit(-1);  
        }  
        else  
        {  
            printf("[%s:%d]",inet_ntoa(seraddr.sin_addr),ntohs(seraddr.sin_port));  
            printf("%s\n",buf);  
        }  
    }  
    return 0;  
}  
