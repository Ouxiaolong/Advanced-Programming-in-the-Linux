/**
  ******************************************************************************
  * @file    send.c
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
    int on = 1;  
    char buf[N] = "This is a broadcast package!";  
    struct sockaddr_in dstaddr;  
  
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
    memset(&dstaddr, 0, sizeof(dstaddr));  
    dstaddr.sin_family = AF_INET;  
    dstaddr.sin_port = htons(PORT);  
    dstaddr.sin_addr.s_addr = inet_addr("192.168.0.110"); // 192.168.1.x ���εĹ㲥��ַ  
    if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0) //�׽���Ĭ�ϲ������͹㲥����ͨ���޸� SO_BROADCAST ѡ��ʹ��  
    {  
        perror("setsockopt error");  
        exit(-1);  
    }  
    while(1)  
    {  
        sendto(sockfd, buf, N, 0,(struct sockaddr *)&dstaddr, sizeof(dstaddr));  
        sleep(1);  
    }  
    return 0;  
}  
