
#include "types.h"
#include "user.h"
#include "debug.h"

#define CHILD_PROCS 4

int main(void) {
  for (int i = 0; i < CHILD_PROCS; i++)
    if (fork() == 0) {
      volatile int j = 1;
      for (int i = 0; i < 1000000000; i++) j = (j > 10000)?j + (j % 13): j % 111;
      printf(1, "%d \n", j);
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