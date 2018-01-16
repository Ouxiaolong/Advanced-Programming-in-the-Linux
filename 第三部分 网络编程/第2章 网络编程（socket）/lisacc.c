/**
  ******************************************************************************
  * @file    lisacc.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
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
#define PORT 2345  
  
int main()  
{  
    int sockfd,newsockfd;  
    struct sockaddr_in addr,caddr;  
    int addr_len = sizeof(struct sockaddr_in);  
    int caddr_len = sizeof(struct sockaddr_in);  
  
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)  
    {  
        perror("socket error");  
        exit(-1);  
    }  
    else  
    {  
        printf("socket successfully!\n");  
        printf("socket id : %d\n",sockfd);  
    }  
  
    memset(&addr,0,addr_len);  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(PORT);  
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
    if(bind(sockfd,(struct sockaddr *)&addr,addr_len) == -1)  
    {  
        perror("bind error");  
        exit(-1);  
    }  
    else  
    {  
        printf("bind successfully!\n");  
        printf("local port : %d\n",PORT);  
    }  
  
    if(listen(sockfd,5) == -1)  
    {  
        perror("listen error");  
        exit(-1);  
    }  
    else  
    {  
        printf("listening...\n");  
    }  
  
    if((newsockfd = accept(sockfd,(struct sockaddr *)&caddr,&caddr_len)) == -1)  
    {  
        perror("accept error");  
        exit(-1);  
    }  
    else  
    {  
        printf("accepted a new connection ..\n");  
        printf("new socket id : %d\n",newsockfd);  
    }  
  
    return 0;  
}
