#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
  for (int k = 0; k < 30; k++ ) {
    pid = fork ();
    if ( pid < 0 ) {
      printf(1, "%d failed in fork!\n", getpid());
    } else if (pid > 0) {
      // parent
      printf(1, "Parent %d creating child %d\n",getpid(), pid);
      wait();
      }
      else {
	printf(1,"Child %d created\n",getpid());
    if (getpid() < 6)
        changepriority(getpid(),6);
    else if (getpid() < 11)
        changepriority(getpid(),5);
    else if (getpid() < 16)
        changepriority(getpid(),4);
    else if (getpid() < 21)
        changepriority(getpid(),3);
    else if (getpid() < 26)
        changepriority(getpid(),2);
    else if (getpid() < 31)
        changepriority(getpid(),1);

	for(int i = 0; i < 250; i++)
	    printf(1,"/%d/ : /%d/\n",getpid(), i + 1);
	break;
      }
  }
  exit();
}