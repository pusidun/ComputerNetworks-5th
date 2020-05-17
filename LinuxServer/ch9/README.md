### select

```
#include<sys/select.h>
int select(int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, struct timeval *timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

struct timeout {
    long tv_sec;
    long tv_usec;
};
```

### epoll

```
#include<sys/epoll.h>
int epoll_create(int size);

int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);
EPOLL_CTL_ADD
EPOLL_CTL_MOD
EPOLL_CTL_DEL

struct epoll_event {
    __uint32_t events;
    epoll_data_t data;
};

epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);
