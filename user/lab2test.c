#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_PROC 10
int main(int argc, char * argv[]) {
  int n_proc, ret;
  if (argc < 2) {
    printf("Usage: %s [SLEEP] [N_PROC] [TICKET1] [TICKET2]...\n", argv[0]);
    exit(-1);
  }
  n_proc = atoi(argv[1]);
  if (n_proc > MAX_PROC) {
    printf("Cannot test with more than %d processes\n", MAX_PROC);
    exit(-1);
  }
  for (int i = 0; i < n_proc; i++) {
    sleep(1);
    ret = fork();
    if (ret == 0) { // child process
      malloc(4096); // this triggers a syscall
      while (1);
    } else { // parent
      continue;
    }
  }
  sleep(1);
  sched_statistics();
  exit(0);
}