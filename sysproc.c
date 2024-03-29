#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "debug.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getppid(void)
{
  return myproc()->parent->pid;
}

int
sys_getchildspid(void)
{
  int *ar, size;

  if (argint(0, &size) < 0)
    return -1;
  if (argptr(1, (void *)&ar, size) < 0)
    return -1;
  getchildspid(size, ar);
  return 1;
}

int
sys_getsyscallcounter(void)
{
  int syscall_num;
  if (argint(0, &syscall_num) < 0)
    return -1;
  return myproc()->systemcall_stat[syscall_num];
}

int
sys_dwait(void)
{
  struct procstat *st;
  if (argptr(0, (void *)&st, sizeof(struct procstat)) < 0)
    return -1;
  return dwait(st);
}

int sys_changepriority(void) {
  int pid, priority;
  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &priority) < 0)
    return -1;

  return changepriority(pid, priority);
}

int
sys_chshcpolicy(void)
{
  int n;
  if (argint(0, &n) < 0)
    return -1;
  chshcpolicy(n);
  return 1;
}

int
sys_changequeue(void)
{
  int pid, qn;
  if (argint(0, &pid) < 0)
    return -1;
  if (argint(1, &qn) < 0)
    return -1;
  changequeue(pid, qn);
  return 1;
}
