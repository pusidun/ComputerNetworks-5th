#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include"../debug.hpp"

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main()
{
    int fd;
    if( (fd = open("file.hole", O_RDWR|O_CREAT|O_TRUNC)) <0)
        log_err("create err");

    if(write(fd, buf1, 10) != 10)
        log_err("buf1 write err");

    if( lseek(fd, 163, SEEK_SET) == -1)
        log_err("lseek err");

    if(write(fd, buf2, 10) != 10)
        log_err("write buf2 err");

    exit(0);
}