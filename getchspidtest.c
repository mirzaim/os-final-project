
#include "types.h"
#include "stat.h"
#include "user.h"

#define SIZE 10
#define CHILD_PROCS 5

int main(void) {
    int ar[SIZE];
    int parent_pid = getpid();
    printf(1, "This is process %d and will call the fork.\n", parent_pid);
    for (int i = 0; i < CHILD_PROCS; i++)
        if (fork() == 0){
            sleep(5);
            exit();
        }
    
    if (parent_pid == getpid()){
        printf(1, "This is process %d and will call the getchildspid.\n", parent_pid);
        getchildspid(SIZE, ar);
        for (int i = 0; ar[i] >= 0; i++)
            printf(1, "%d/", ar[i]);
        printf(1, "\n");
        for (int i = 0; i < CHILD_PROCS; i++)
            wait();
    }

   exit();
}