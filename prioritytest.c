
#include "types.h"
#include "debug.h"
#include "schedule.h"
#include "user.h"

#define CHILD_PROCS 30
#define NUM_PRINT 250

int main(void) {
  chshcpolicy(PRIORITY_SCH);
  for (int i = 0; i < CHILD_PROCS; i++)
    if (fork() == 0) {
      printf(1, "Child %d created\n", getpid());
      if (i < 5)
        changepriority(getpid(), 6);
      else if (i < 10)
        changepriority(getpid(), 5);
      else if (i < 15)
        changepriority(getpid(), 4);
      else if (i < 20)
        changepriority(getpid(), 3);
      else if (i < 25)
        changepriority(getpid(), 2);
      else if (i < 30)
        changepriority(getpid(), 1);
      for (int i = 0; i < NUM_PRINT; i++)
        printf(1, "/%d/ : /%d/\n", getpid(), i + 1);
      exit();
    }
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