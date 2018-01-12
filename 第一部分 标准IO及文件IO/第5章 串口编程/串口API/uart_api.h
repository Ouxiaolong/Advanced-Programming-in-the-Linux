
#ifndef _UART_API_H_
#define _UART_API_H_
 
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE  36
//#define DEVICE_M0 "/dev/ttyUSB0"
#define DEVICE_GSM "/dev/ttyUSB0"

int set_com_config(int fd,int baud_rate, int data_bits,char parity,int stop_bits);
int open_port(char *com_port);
int init_port(char *com_port);

#endif


