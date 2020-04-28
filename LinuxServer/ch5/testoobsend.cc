#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[]) {
    if(argc <= 2) {
        printf("USAGE: ip port\n");
        return 1;
    }
    char* ip = argv[1];
    int port = atoi(argv[2]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock != -1);
    sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);

    if(connect(sock, (struct sockaddr*)&address, sizeof(address)) < 0)
        printf("connection failed.\n");
    else {
        const char* oob_data = "abc";
        const char* normal_data = "123";
        send(sock, normal_data, strlen(normal_data),    0);
        send(sock, oob_data,    strlen(oob_data),       MSG_OOB);
        send(sock, normal_data, strlen(normal_data),    0);
    }

    close(sock);
    return 0;
}
