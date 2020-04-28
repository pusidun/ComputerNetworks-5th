#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<errno.h>

int main(int argc, char* argv[]) {
    if(argc <= 2) {
        printf("Usage: ip port");
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock != -1);
    sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &address.sin_addr);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    sockaddr_in client;
    socklen_t len = sizeof(client);
    bzero(&client, sizeof(client));
    int conn = accept(sock, (struct sockaddr*)&client, &len);
    if(conn < 0)
        printf("errno is:%d\n", errno);
    else {
        char remote[INET_ADDRSTRLEN];
        
        printf("remote %s port:%d\n", inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN),
                 ntohs(client.sin_port));
        close(conn);
    }
    close(sock);
    return 0;
}
