#ifndef _FILELOCK_H_
#define _FILELOCK_H_

#include <unistd.h>
#include <fcntl.h>

/* 设置一把读锁 */
int readLock(int fd, short start, short whence, short len) ;

/* 设置一把读锁 , 不等待 */
int readLocknw(int fd, short start, short whence, short len) ;

/* 设置一把写锁 */
int writeLock(int fd, short start, short whence, short len) ;

/* 设置一把写锁 */
int writeLocknw(int fd, short start, short whence, short len) ;

/* 解锁 */
int unlock(int fd, short start, short whence, short len) ;

#endif
