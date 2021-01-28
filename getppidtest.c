
#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    printf(1, "This is process %d and will call the fork.\n", getpid());
    if (fork() == 0)
        printf(1, "This is process %d and the parent id is %d.\n", getpid(), getppid());
    else
        wait();
   exit();
}