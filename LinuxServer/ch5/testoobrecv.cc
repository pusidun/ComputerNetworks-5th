#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>

#define BUFFSIZE 1024

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("USAGE:ip port\n");
        return 1;
    }
    char* ip = argv[1];
    int port = atoi(argv[2]);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);
    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    assert(ret != -1);
    ret = listen(sockfd, 5);
    assert(ret != -1);

    sockaddr_in clientfd;
    socklen_t clientlen = sizeof(clientfd);
    int conn = accept(sockfd, (struct sockaddr*)&clientfd, &clientlen);
    if(conn < 0)
        printf("connect failed\n");
    else {
        char buff[BUFFSIZE];
        memset(buff, 0, BUFFSIZE);
        ret = recv(conn, buff, BUFFSIZE-1, 0);
        printf("get %d bytes of normal data:%s\n", ret, buff);

        sleep(3); // 这里如果还未发送带外数据，就开始接收，会报Invalid argument错误，所以sleep一下
        memset(buff, 0, BUFFSIZE);
        ret = recv(conn, buff, BUFFSIZE-1, MSG_OOB);
        printf("get %d bytes of normal data:%s\n", ret, buff);
        printf("%d %s\n", errno, strerror(errno));

        memset(buff, 0, BUFFSIZE);
        ret = recv(conn, buff, BUFFSIZE-1, 0);
        printf("get %d bytes of normal data:%s\n", ret, buff);

        close(conn);
    }
    close(sockfd);
    return 0;
}
