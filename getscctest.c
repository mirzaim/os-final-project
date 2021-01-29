

#include "types.h"
#include "syscall.h"
#include "user.h"

#define CHILD_PROCS 5

int main(void) {
  printf(1, "This is process %d and number of getpid system call is %d.\n",
         getpid(), getsyscallcounter(SYS_getpid));
  printf(1, "This is process %d and will call the fork.\n", getpid());
  for (int i = 0; i < CHILD_PROCS; i++)
    if (fork() == 0) {
      sleep(5);
      exit();
    }

  printf(1, "This is process %d and number of fork system call is %d.\n",
         getpid(), getsyscallcounter(SYS_fork));
  
  for (int i = 0; i < CHILD_PROCS; i++) wait();

  exit();
}