#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "common.h"
#include "atom.h"

void atom_process(char atom, int pid, int TI, sem_t *sem_start, data_t *data_ptr) {
    srand(getpid());
    int *line_num_ptr = &(data_ptr->line_num);

    atom_start(atom, pid, sem_start, line_num_ptr);
    atom_queue(atom, pid, TI, sem_start, line_num_ptr);

}

// start atom process and log a message
void atom_start(char atom, int pid, sem_t *sem_start, int *line_num_ptr) {
    sem_wait(sem_start);
    log_line(line_num_ptr);
    log_started(atom, pid);
    sem_post(sem_start);
}

// add atom to queue and log a message
void atom_queue(char atom, int pid, int TI, sem_t *sem_start, int *line_num_ptr) {
    sem_wait(sem_start);
    random_sleep_ms(0, TI);
    log_line(line_num_ptr);
    log_queue(atom, pid);
    sem_post(sem_start);
}
