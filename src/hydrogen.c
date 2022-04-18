#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "logger.h"
#include "hydrogen.h"
#include "utils.h"

static const char atom = 'H';

void hydrogen_process(int pid, int TI, sem_t *sem_start) {
    srand(getpid());
    sem_wait(sem_start);
    log_started(atom, pid);
    sem_post(sem_start);

    sem_wait(sem_start);
    random_sleep_ms(0, TI);
    log_queue(atom, pid);
    sem_post(sem_start);

}
