/**
  ******************************************************************************
  * @file    alarm.c
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
#include <signal.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#define N 64  
#define PORT 8888  
  
void handler(int signo)  
{  
    printf("interrupted by SIGALRM\n");  
}  
  
int main()  
{  
    int sockfd;  
    char buf[N];  
    struct sockaddr_in seraddr;  
    struct sigaction act;  
  
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
    sigaction(SIGALRM, NULL, &act);  
    act.sa_handler = handler;  
    act.sa_flags &= ~SA_RESTART;  
    sigaction(SIGALRM, &act, NULL);  
  
    alarm(6);  
    if(recvfrom(sockfd, buf, N, 0, NULL, NULL) < 0)  
    {  
        perror("fail to recvfrom");  
        exit(-1);  
    }  
    printf("recv data: %s\n",buf);  
    alarm(0);  
  
    return 0;  
}
