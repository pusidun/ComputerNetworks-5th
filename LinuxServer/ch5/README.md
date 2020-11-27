### convert values between host and network byte order
```
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```

### 通用socket地址

```
#include<bits/socket.h>
struct sockaddr{
    sa_family_t sa_family;
    char sa_data[14];
}
```

### 专用socket地址
```
#include<sys/types.h>
#include<sys/socket.h>

struct sockaddr {
    sa_family_t sa_family;
    char        sa_data[14];
};
/*ipv4*/
struct sockaddr_in {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
};
struct in_addr {
    uint32_t s_addr;
};
/*ipv6*/
struct sockaddr_in6 {
    sa_family_t sin6_family;
    in_port_t sin6_port;
    uint32_t sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t sin6_scope_id;
}
struct in6_addr {
    unsigned char s6_addr[16];
}
/*unix*/
#define UNIX_PATH_MAX 108
struct sockaddr_un {
    sa_family_t sun_family;
    char sun_path[UNIX_PATH_MAX];
};
```

### IP地址转换
```
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

in_addr_t inet_addr(const char *cp);  // failed ret: INADDR_NONE
int inet_aton(const char *cp, struct in_addr *inp);
char *inet_ntoa(struct in_addr in);  // 不可重入，内部有静态变量存储转化结果

#include <arpa/inet.h>
int inet_pton(int af, const char *src, void *dst);
// size: INET_ADDRSTRLEN 16     INET6_ADDRSTRLEN 46
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
```

### 创建socket

```
#include<sys/types.h>
#include<sys/socket.h>
int socket(int domain, int type, int protocal);
```

### 命名socket
```
#include<sys/types.h>
#include<sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

### 监听socket
```
#include <sys/types.h>
#include <sys/socket.h>
int listen(int sockfd, int backlog);
```

### 接收连接
```
#include <sys/types.h>
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

### 关闭连接
```
/*并非立刻关闭,引用计数将为0时才真正关闭*/
include<unistd.h>
int close(int fd);

/*SHUT_RD,SHUT_WR,SHUT_RDWR*/
#include<sys/socket.h>
int shutdown(int fd, int howto);
```

### 数据读写

#### TCP
```
#include<sys/socket.h>
#include<sys/types.h>
ssize_t recv(int sockfd, void* buff, size_t len, int flag);
ssize_t send(int sockfd, const void* buff, size_t len, int flag);
```

#### UDP
```
#include <sys/types.h>
#include <sys/socket.h>
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);
```
recvfrom和sendto也可以作为TCP的读写API，只需要将最后两个参数设置为NULL

#### 通用
```
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
```

### 带外标记

```
#include<sys/socket.h>
int sockatmark(int sockfd);
```
返回1，就可以利用带MSG_OOB标志的recv调用来接受带外数据

### 地址信息函数
```
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);  // 本端
int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);  // 对端
```

### socket选项

```
#include<sys/socket.h>
int getsockopt(int sockfd, int level, int option_name, void* option_value,
                socklen_t* restrict option_len);
int setsockopt(int sockfd, int level, int option_name, const void* option_value,
                socklen_t option_len);
```

成功时返回0，失败时返回-1并设置errno

#### so_reuseaddr

强制使用处于TIME_WAIT的TCP socket

```
int sock = sock(PF_INET, SOCK_STREAM, 0);
assert(sock >= 0);
int reuse = 1;
setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

struct sockaddr_in address;
bzero(&address);
address.sin_family = AF_INET;
inet_pton(AF_INET, ip, &address.sin_addr);
address.port = htons(port);
int ret = bind(sock, (struct sockaddr*)address, sizeof(address));
```

#### so_rcvbuf so_sndbuf

设置发送接受缓冲区。接受缓冲区最小值256字节，发送缓冲区最小值2048字节。

```
setsockopt(sock, SOL_SOCKET, SO_RCVBUF /*SO_SNDBUF*/, &recvbuff, sizeof(recvbuf));
getsockopt(sock, SOL_SOCKET, SO_RCVBUF /*SO_SNDBUF*/, &recvbuff, (socklen_t*)&len);
```

#### so_rcvlowat so_sndlowat

接受和发送缓冲区低水位标记，默认都是1字节

当接受缓冲区可读数据大于低水位标记，IO复用通知应用程序可读；当发送缓冲区空闲空间大于低水位标志，IO复用通知应用程序可写

#### so_linger

```
#include<sys/socket.h>
struct linger{
    int l_onoff;
    int l_linger;
}
```

### 网络信息API

#### gethostbyname gethostbyaddr

```
#include <netdb.h>
struct hostent *gethostbyname(const char *name);
#include <sys/socket.h>       /* for AF_INET */
struct hostent *gethostbyaddr(const void *addr,
                                socklen_t len, int type);

struct hostent {
               char  *h_name;            /* official name of host */
               char **h_aliases;         /* alias list */
               int    h_addrtype;        /* host address type */
               int    h_length;          /* length of address */
               char **h_addr_list;       /* list of addresses */
           }                                
```

#### getservbyname getservbyport

```
include<netdb.h>
struct servent* getservbyname(const char* name, const char* proto);
struct servent* getservbyport(int port, const char* proto);
```

#### getaddrinfo

#### getnameinfo
