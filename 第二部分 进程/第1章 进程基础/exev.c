/**
  ******************************************************************************
  * @file    exev.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   execlp ����ʹ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>  
#include <unistd.h>  
  
int main()  
{  
	//����execlp �������൱�ڵ����� "ps -ef"����  
    if(execlp("ps","ps","-ef",NULL) < 0) //����"ps"Ϊfilename "ps" Ϊargv[0] "-ef"Ϊargv[1]��NULLΪ����������־  
    {  
        perror("execlp error");  
        return -1;  
    }  
  
    return 0;  
}  
