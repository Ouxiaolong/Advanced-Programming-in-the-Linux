/**
  ******************************************************************************
  * @file    setsockopt.c
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
    struct timeval t = {6, 0};  
  
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
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
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
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(t)) < 0)  
    {  
        perror("setsockopt error");  
        exit(-1);  
    }  
    if(recvfrom(sockfd, buf, N, 0, NULL, NULL) < 0)  
    {  
        perror("fail to recvfrom");  
        exit(-1);  
    }  
    else  
    {  
        printf("recv data: %s\n",buf);  
    }  
    return 0;  
}  
