#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "common.h"
#include "atom.h"

void atom_process(char atom, int pid, int TI, data_t *data_ptr) {
    srand(getpid());

    atom_start(atom, pid, data_ptr);
    atom_queue(atom, pid, TI, data_ptr);
    // create_molecule(atom, pid, sem_mol, data_ptr);
}

// start atom process and log a message
void atom_start(char atom, int pid, data_t *data_ptr) {
    sem_wait(data_ptr->sem_start);

    // pointer to variable in shared memory with the number of lines printed
    int *line_num_ptr = &(data_ptr->line_num);
    log_line(line_num_ptr);
    log_started(atom, pid);

    sem_post(data_ptr->sem_start);
}

// add atom to queue and log a message
void atom_queue(char atom, int pid, int TI, data_t *data_ptr) {
    sem_wait(data_ptr->sem_start);

    // pointer to variable in shared memory with the number of lines printed
    int *line_num_ptr = &(data_ptr->line_num);

    // increase the number of atoms queued
    data_ptr->atoms_queued += 1;

    // sleep for random time 
    random_sleep_ms(0, TI); 

    // log atom queue
    log_line(line_num_ptr); 
    log_queue(atom, pid);

    sem_post(data_ptr->sem_start);
}

/*
void create_molecule(char atom, int pid, data_t *data_ptr) {
    sem_wait(sem_mol);

    // pointer to variable in shared memory with the number of lines printed
    int *line_num_ptr = &(data_ptr->line_num);

    // pointer to variable in shared memory with the number of molecules created
    int *mol_num_ptr = &(data_ptr->mol_num);

    // log molecule start
    log_line(line_num_ptr);
    log_molecule(atom, pid, mol_num_ptr);

    sem_post(sem_mol);
}
*/
