#include<cstdio>

int main() {
    union edian {
        short num;
        unsigned char buff[sizeof(short)];
    };
    union edian var;
    var.num = 0x8a02;  // 这里如果buff不是unsigned char,var.num注意不要越界了,超过127会变为负数，下面无法判断
    if(var.buff[0] == 0x8a && var.buff[1] == 0x02)
        printf("big endian\n");
    else if(var.buff[0] == 0x02 && var.buff[1] == 0x8a)
        printf("little endian\n");
    printf("%x %x\n", var.buff[0], var.buff[1]);
    return 0;
}