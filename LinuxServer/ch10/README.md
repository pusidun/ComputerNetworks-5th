```
/* 发送 */
#include<sys/types.h>
#include<signal.h>
int kill(pid_t pid, int sig);

pid>0
pid=0   本进程组内其他进程
pid=-1  出init外所有进程
pid<-1  组ID为-pid的进程组所有成员

/* 接收 */
#include<signal.h>
typedef void (*__sighandler_t)(int);

```