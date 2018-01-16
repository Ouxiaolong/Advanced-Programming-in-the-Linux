/**
  ******************************************************************************
  * @file    ftok.c
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>         
#include <stdlib.h>    
#include <sys/stat.h>  
  
int main()  
{
	char    filename[50];     
    struct stat    buf;  
	int     ret;  

	strcpy( filename, "." );  
	ret = stat( filename, &buf );  

	if( ret )  
	{
		printf( "stat error\n" );  
		return -1;  
	}  
	printf( "the file info: ftok( filename, 0x27 ) = %x, st_dev = %x, st_ino= %x\n", ftok( filename, 0x27 ),  buf.st_dev,buf.st_ino );  
  
    return 0;  
}