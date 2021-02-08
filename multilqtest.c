
#include "types.h"
#include "user.h"
#include "debug.h"
#include "schedule.h"

#define CHILD_PROCS 25
#define NUM_PRINT 250

int main(void) {
  for (int i = 0; i < CHILD_PROCS; i++)
    if (fork() == 0) {
      printf(1, "Child %d created\n", getpid());
      if (i < 5)
        changequeue(getpid(), PAR_PRIO_MULTI);
      else if (i < 10)
        changequeue(getpid(), RR_MULTI);
      else if (i < 15) {
        changequeue(getpid(), PRIO_MULTI);
        changepriority(getpid(), 2);
      } else if (i < 20) {
        changequeue(getpid(), PRIO_MULTI);
        changepriority(getpid(), 1);
      } else if (i < 25)
        changequeue(getpid(), FCFS_MULTI);

      sleep(100);
      if (i == CHILD_PROCS - 1) chshcpolicy(MULTILAYER);

      for (int i = 0; i < NUM_PRINT; i++)
        printf(1, "/%d/ : /%d/\n", getpid(), i + 1);
      exit();
    } else
      sleep(1);

  struct procstat ps[CHILD_PROCS];
  int pid[CHILD_PROCS], mean;
  for (int i = 0; i < CHILD_PROCS; i++) pid[i] = dwait(&ps[i]);

  for (int i = 0; i < CHILD_PROCS; i++) {
    mean = (ps[i].cpu_burst + ps[i].turnaround + ps[i].waiting_time) / 3;
    printf(1, "%d: cpu_burst: %d, turnaround: %d, waiting_time: %d, mean: %d\n",
           pid[i], ps[i].cpu_burst, ps[i].turnaround, ps[i].waiting_time, mean);
  }
  exit();
}