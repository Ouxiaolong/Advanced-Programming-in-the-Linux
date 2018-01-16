/**
  ******************************************************************************
  * @file    socket.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   socket使用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  

#define PORT 2345  
  
int main()  
{  
    int sockfd;  
    struct sockaddr_in addr;  
    int addr_len = sizeof(struct sockaddr_in);  
  
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)  
    {  
        perror("socket fail");  
        exit(-1);  
    }  
    else  
    {  
        printf("socket created successfully!\nsocket id is %d\n",sockfd);  
    }  
  
    memset(&addr,0,addr_len);  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(PORT);  
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
    if(bind(sockfd,(struct sockaddr *)(&addr),addr_len) < 0)  
    {  
        perror("bind error");  
        exit(-1);  
    }  
    else  
    {  
        printf("bind port successfully!\nlocal port:%d\n",PORT);  
    }  
    return 0;  
} 
