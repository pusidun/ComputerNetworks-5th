#include<sys/socket.h>
#include<sys/types.h>
#include<signal.h>
#include<unistd.h>
#include<assert.h>
#include<strings.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>

static bool stop = false;

static void handle_term(int) {
    stop = true;
}

int main(int argc, char** argv) {
    signal(SIGTERM, handle_term);
    if(argc <= 3) {
        printf("params less than 3");
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, backlog);
    assert(ret != -1);
    while(!stop)
        sleep(1);
    close(sock);
    return 0;
}
