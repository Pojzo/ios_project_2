#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "oxygen.h"

static const char atom = 'O';

void oxygen_process(int pid, int TI, sem_t *sem_start) {
    srand(getpid());
    sem_wait(sem_start);
    log_started(atom, pid);
    sem_post(sem_start);

    sem_wait(sem_start);
    random_sleep_ms(0, TI);
    log_queue(atom, pid);
    sem_post(sem_start);
}
