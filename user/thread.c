#include "thread.h"

void lock_init(struct lock_t* lock) {
    lock->locked = 0;
}

void lock_acquire(struct lock_t* lock) {
    while(__sync_lock_test_and_set(&lock->locked, 1) != 0);
}

void lock_release(struct lock_t* lock) {
    lock->locked = 0;
}

// 1) Allocate a user stack of PGSIZE bytes
// 2) Call clone() to create a child thread
// 3) For parent: return 0 on success, -1 on fail
// 4) For child: Call start_routine() w/ argument `arg`
// 5) When start_routine() returns, terminate child w/ exit()
int thread_create(void *(start_routine)(void *), void *arg) {
    void* newStack = malloc(PGSIZE);
    int childPID = 0;
    if ((childPID = clone(newStack)) == 0) { // Child code
        start_routine(arg);
        exit(0);
    } else if (childPID < 0) { // Error occurred
        return -1;
    }
    return 0; // Parent returns this on success
}
