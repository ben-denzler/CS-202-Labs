#include "kernel/types.h"
#include "kernel/riscv.h"  // Defines PGSIZE
#include "kernel/param.h"
#include "kernel/memlayout.h"
#include "kernel/spinlock.h"
#include "kernel/proc.h"
#include "kernel/defs.h"

struct lock_t {
    uint64 locked;
};

int thread_create(void *(start_routine)(void *), void *arg);
void lock_init(struct lock_t *lock);
void lock_acquire(struct lock_t *lock);
void lock_release(struct lock_t *lock);