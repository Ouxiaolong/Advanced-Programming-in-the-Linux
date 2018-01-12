/**
  ******************************************************************************
  * @file    uart_api.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   串口设置
  ******************************************************************************
  * @attention
  * @开发平台 A9
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include "uart_api.h"
 
/*
 * @函数名：set_com_config
 * @函数功能：串口设置函数
 */
 int set_com_config(int fd,int baud_rate,int data_bits, char parity, int stop_bits)	
{
	struct termios new_cfg;
	int speed;
							    
	/* 保存并测试现有串口参数设置，在这里如果串口号等出错，会有相关的出错信息 */
	
	if (tcgetattr(fd, &new_cfg) != 0) 
	{
		perror("tcgetattr save");	
		return -1;
	}
	//修改控制模式，保证程序不会占用串口  
	new_cfg.c_cflag |= CLOCAL;  
	//修改控制模式，使得能够从串口中读取输入数据  
	new_cfg.c_cflag |= CREAD;  
	new_cfg.c_oflag &= ~(ONLCR | OCRNL);
	new_cfg.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	new_cfg.c_iflag &= ~(ICRNL | INLCR);
	new_cfg.c_iflag &= ~(IXON | IXOFF | IXANY);
	
	/* 设置波特率 */
	switch (baud_rate)
	{
		case 2400:	
		{
			speed = B2400;	
		}
		break;		
		case 4800:
		{
			speed = B4800;
		}
		break;
		case 9600:
		{
			speed = B9600;
		}
		break;
		case 19200:
		{
			speed = B19200;
		}
		break;
		case 38400:	
		{
			speed = B38400;
		}
		break;
		default:			
		case 115200:		
		{
			speed = B115200;			
		}		
		break;		
	}
	
	cfsetispeed(&new_cfg, speed);//输入波特率	
	cfsetospeed(&new_cfg, speed);//输出波特率
	switch (data_bits) /* 设置数据位 */	
	{		
		case 7:
		{
			new_cfg.c_cflag |= CS7;		
		}		
		break;	
		default:	
		case 8:
		{
			new_cfg.c_cflag |= CS8;
		}		
		break;		
	}
	
	switch (parity) /* 设置奇偶校验位 */	
	{
		default:	
		case 'n':	
		case 'N':	
		{
			new_cfg.c_cflag &= ~PARENB; 
			new_cfg.c_iflag &= ~INPCK; 	
		}	
		break;	
		case 'o':
		case 'O':
		{
			new_cfg.c_cflag |= (PARODD | PARENB); 
			new_cfg.c_iflag |= INPCK; 
		}	
		break;		
		case 'e':
		case 'E':
		{
			new_cfg.c_cflag |= PARENB; 
			new_cfg.c_cflag &= ~PARODD; 
			new_cfg.c_iflag |= INPCK; 				
		}	
		break;			
		case 's': /* as no parity */		
		case 'S':
		{
			new_cfg.c_cflag &= ~PARENB;
			new_cfg.c_cflag &= ~CSTOPB;
		}	
		break;	
	}
	switch (stop_bits) /* 设置停止位 */	
	{
		default:
		case 1:
		{
			new_cfg.c_cflag &= ~CSTOPB;		
		}	
		break;	
		case 2:
		{
			new_cfg.c_cflag |= CSTOPB;		
		}
	}
	//修改输出模式，原始数据输出  
	new_cfg.c_oflag &= ~OPOST;  
	new_cfg.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//我加的  
	new_cfg.c_lflag &= ~(ISIG | ICANON);  

	//设置等待时间和最小接收字符  
	new_cfg.c_cc[VTIME] = 0; /* 读取一个字符等待0*(0/10)s */    
	new_cfg.c_cc[VMIN] = 1; /* 读取字符的最少个数为0 */  

	//如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读
	tcflush(fd, TCIFLUSH); /* 处理未接收字符 */	
	if ((tcsetattr(fd, TCSANOW, &new_cfg)) != 0) /* 激活新配置 */	
	{
		perror("tcsetattr action");
		return -1;	
	} 
	printf("serial set success\n");
	return 0;	
}

/*
 * @函数名：open_port
 * @返回值：fd
 * @函数功能：打开串口函数
 */
int open_port(char *com_port)
{
	int fd;

	/*分别为com1，com2， com3对应 ttyUSB0 ttyUSB1 ttyUSB2 */			    
	fd = open( com_port, O_RDWR|O_NOCTTY|O_NDELAY);  		 
	if (fd < 0)  
	{
		perror("Can't Open Serial Port");  
		return -1;										     
	}
	/*恢复串口为阻塞状态*/
	if (fcntl(fd,F_SETFL,0)<0)
	{
		perror("fcntl F_SETFL\n");
	}
	/*测试是否为终端设备*/
	if(isatty(STDIN_FILENO) == 0)
	{
		perror("standard input is not a terminal device");
	}
	return fd;
}

/*
 * @函数名：init_port
 * @输出参数：com_port
 * @返回值：fd
 * @函数功能：串口初始化函数
 */
int init_port(char *com_port)
{
	int fd;

	if ((fd = open_port(com_port)) < 0 )
	{
		perror("open_port");
		return -1;
	}
	printf("open port success\n");
	if(set_com_config(fd,115200,8,'N',1) < 0)
	{
		perror("set_com_config");
		return -1;
	}
	return fd;
}

