#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<cstdlib>
#include<sys/epoll.h>

#define LISTENQ 5
#define IPADDR "127.0.0.1"
#define PORT 4000
#define FDSIZE 1000
#define EPOLLEVENTS 100
#define MAXSIZE 1024

int sock_bind(char* ip, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) { perror("sock error"); exit(1);}
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip ,&addr.sin_addr);
    if(0 > bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)))
        exit(1);
    return sockfd;
}

void epoll_modify(int epollfd, int events, int fd) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

void do_epoll(int listenfd) {
    int epollfd = epoll_create(FDSIZE);
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev);
    struct epoll_event events[EPOLLEVENTS];
    char buff[MAXSIZE];
    while(1) {
        int nfd = epoll_wait(epollfd, events, EPOLLEVENTS, 50);
        for(int i = 0; i<nfd; ++i) {
            int fd = events[i].data.fd;
            if((fd == listenfd) && (events[i].events & EPOLLIN)) {
                struct sockaddr_in chiaddr;
                socklen_t chiladdrlen = 0;
                bzero(&chiaddr, sizeof(chiaddr));
                int childfd = accept(listenfd, (struct sockaddr*)&chiaddr, &chiladdrlen);
                struct epoll_event ev;
                ev.data.fd = childfd;
                ev.events = EPOLLIN;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, childfd, &ev);
            }
            else if(events[i].events & EPOLLIN) {
                int nread = read(events[i].data.fd, buff, MAXSIZE);
                if(nread <= 0) {
                    struct epoll_event ev;
                    ev.data.fd = events[i].data.fd;
                    ev.events = EPOLLIN;
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                }
                else {
                    printf("read %s", buff);
                    struct epoll_event ev;
                    ev.data.fd = events[i].data.fd;
                    ev.events = EPOLLOUT;
                    epoll_ctl(epollfd, EPOLL_CTL_MOD, events[i].data.fd, &ev);
                }
            }
            else if(events[i].events & EPOLLOUT) {
                int nwrite = write(events[i].data.fd, buff, strlen(buff));
                if(nwrite == -1) {
                    perror("write error\n");
                    close(events[i].data.fd);
                    struct epoll_event ev;
                    ev.data.fd = events[i].data.fd;
                    ev.events = EPOLLIN;
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                }
                else {
                    epoll_modify(epollfd, EPOLLIN, events[i].data.fd);
                }
            }
        }
    }
    close(epollfd);
}

int main() {
    int listenfd = sock_bind(IPADDR, PORT);
    listen(listenfd, LISTENQ);
    do_epoll(listenfd);
    return 0;
}