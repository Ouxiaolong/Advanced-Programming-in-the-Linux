/**
  ******************************************************************************
  * @file    thread.c
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
#include <pthread.h>  
  
char message[32] = "Hello World!";  
void *thread_function(void *arg);  
  
int main()  
{  
    pthread_t a_thread;  
    void *thread_result;  
  
    if(pthread_create(&a_thread,NULL,thread_function,(void *)message) < 0)  
    {  
        perror("fail to pthread_create");  
        exit(-1);  
    }  
  
    printf("waiting for thread to finish\n");  
    if(pthread_join(a_thread,&thread_result) < 0)  
    {  
        perror("fail to pthread_join");  
        exit(-1);  
    }  
    printf("Message is now %s\n",message);  
    printf("thread_result is %s\n",(char *)thread_result);  
    return 0;  
}  
void *thread_function(void *arg)  
{  
    printf("thread_function is running,argument is %s\n",(char *)arg);  
    strcpy(message,"marked by thread");  
    pthread_exit("Thank you for the cpu time");  
} 
