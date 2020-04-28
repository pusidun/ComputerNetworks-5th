### convert values between host and network byte order
```
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
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
char *inet_ntoa(struct in_addr in);  // 不可重入

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

### 地址信息函数
```
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);  // 本端
int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);  // 对端
```

### socket选项

getsockopt setsockopt

#### so_reuseaddr

#### so_rcvbuf so_sndbuf

#### so_rcvlowat so_sndlowat

#### so_linger

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

#### getaddrinfo

#### getnameinfo
