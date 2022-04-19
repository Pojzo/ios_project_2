#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "common.h"
#include "atom.h"

void atom_process(char atom, int pid, int TI, sem_t *sem_start, sem_t *sem_mol, data_t *data_ptr) {
    srand(getpid());

    atom_start(atom, pid, sem_start, data_ptr);
    atom_queue(atom, pid, TI, sem_start, data_ptr);
    create_molecule(atom, pid, sem_mol, data_ptr);
}

// start atom process and log a message
void atom_start(char atom, int pid, sem_t *sem_start, data_t *data_ptr) {
    sem_wait(sem_start);

    // pointer to variable in shared memory with the number of lines printed
    int *line_num_ptr = &(data_ptr->line_num);
    log_line(line_num_ptr);
    log_started(atom, pid);

    sem_post(sem_start);
}

// add atom to queue and log a message
void atom_queue(char atom, int pid, int TI, sem_t *sem_start, data_t *data_ptr) {
    sem_wait(sem_start);

    int *line_num_ptr = &(data_ptr->line_num);
    random_sleep_ms(0, TI);
    log_line(line_num_ptr);
    log_queue(atom, pid);

    sem_post(sem_start);
}

void create_molecule(char atom, int pid, sem_t *sem_mol, data_t *data_ptr) {
    int *line_num_ptr = &(data_ptr->line_num);
    int *mol_num_ptr = &(data_ptr->mol_num);

    sem_wait(sem_mol);
    log_line(line_num_ptr);
    log_molecule(atom, pid, mol_num_ptr);
    sem_post(sem_mol);
}
