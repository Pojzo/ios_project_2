#include <stdio.h>
#include <unistd.h>
#include "logger.h"
#include "hydrogen.h"
#include "utils.h"

static const char atom = 'H';

void hydrogen_process(int pid, int TI, sem_t *sem_start) {
    sem_wait(sem_start);
    log_started(atom, pid);
    sem_post(sem_start);

    float queue_wait_time = rand_in_range(0, TI);
    sem_wait(sem_start);
    queue_wait_time /= 1000;
    sleep(queue_wait_time);
    log_queue(atom, pid);
    sem_post(sem_start);

}
