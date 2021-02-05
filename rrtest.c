
#include "types.h"
#include "user.h"
#include "debug.h"

#define CHILD_PROCS 4

int main(void) {
  for (int i = 0; i < CHILD_PROCS; i++)
    if (fork() == 0) {
      for (int i = 0; i < 400; i++) printf(1, "%d: %d\n", getpid(), i);
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