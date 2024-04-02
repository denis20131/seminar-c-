#include <unistd.h>
pid_t fork(void)
pid_t p;
if ((p=fork())==-1) {ошибка}
else if (p>0) {отец}
    else (p)
        {cыn}
pid_t getpid(void) свой
      getppid() отца

команда >p.s
void exit(int status);
_exit();
abort()
> ./pr1 && ./pr2
int main()
  exec[e,v]<p,e>
  int execve
  int execl
  int execlp
  int execle
  int execv
  int execvp