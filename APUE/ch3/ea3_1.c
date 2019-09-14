#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"../debug.hpp"

int main()
{
    if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
    {
        log_err("cannot seek\n");
    }
    else
    {
        log_info("seek OK\n");
    }
    exit(0);
}