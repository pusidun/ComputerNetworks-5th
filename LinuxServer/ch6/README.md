### pip
```
#include<unistd.h>
int pip(int fd[2]);
``

### dup dup2
```
#include<unistd.h>
int dup(int file_descriptor);
int dup2(int file_descriptor_one, int file_descriptor_two);
```
失败返回-1
不继承原fd属性

### readv分散读 writev集中写

### sendfile零拷贝

```
#include<sys/sendfile.h>
ssize_t sendfile(int out_fd, int in_fd, off_t* offset, size_t count);
```

### mmap munmap

```
#include<sys/mman.h>
void* mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void* start, size_t length);
```
start: 起始地址, NULL自动分配
length:内存段长度
prot:
- PROT_READ
- PROT_WRITE
- PROT_EXEC
- PROT_NONE 不能被访问
flags 控制内存段内容被修改后的行为

### splice 零拷贝操作
```
#include <fcntl.h>
ssize_t splice(int fd_in, loff_t *off_in, int fd_out,
                loff_t *off_out, size_t len, unsigned int flags);
```

### tee 零拷贝操作
```
#include<fcntl.h>
ssize_t tee(int fd_in, int fd_out, size_t len, unsigned int flags);
```

### fcntl
```
#include<fcntl.h>
int fcntl(int fd, int cmd, ...);
```