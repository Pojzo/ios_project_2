#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "common.h"
#include "atom.h"

void atom_process(char atom, int pid, int TI, sem_t *sem_start, int *ptr) {
    (void) ptr;
    srand(getpid());

    sem_wait(sem_start);
    log_started(atom, pid);
    sem_post(sem_start);

    sem_wait(sem_start);
    random_sleep_ms(0, TI);
    log_queue(atom, pid);
    sem_post(sem_start);
}
