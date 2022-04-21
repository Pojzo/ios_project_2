#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "common.h"
#include "atom.h"

void atom_process(char atom, int atom_idx, int TI, data_t *data_ptr) {
    /*
    srand(getpid());
    if (atom == 'O') {
        sem_wait(&data_ptr->sem_oxygen);
        printf("%d: %c %d: started\n", ++data_ptr->line_num, atom, atom_idx);
        fflush(stdout);
        sem_post(&data_ptr->sem_oxygen);
    }
    else {
        sem_wait(&data_ptr->sem_hydrogen); 
            printf("%d: %c %d: started\n", ++data_ptr->line_num, atom, atom_idx);
        fflush(stdout);
        sem_post(&data_ptr->sem_hydrogen); 
    }
    random_sleep_ms(0, TI); 
    printf("%d: %c %d: going to queue\n", ++data_ptr->line_num, atom, atom_idx);
    */
      

       srand(getpid());
       atom_start(atom, atom_idx, data_ptr);
       atom_queue(atom, atom_idx, TI, data_ptr);
       exit(0);
    // create_molecule(atom, pid, sem_mol, data_ptr);
}


// start atom process and log a message
void atom_start(char atom, int pid, data_t *data_ptr) {
    if (atom == 'O') {
        sem_wait(&(data_ptr->sem_oxygen));

        log_started_queue(atom, pid, data_ptr, 0); 

        sem_post(&(data_ptr->sem_oxygen));
    }
    else {
        sem_wait(&(data_ptr->sem_hydrogen));

        log_started_queue(atom, pid, data_ptr, 0);

        sem_post(&(data_ptr->sem_hydrogen));
    }
}

// add atom to queue and log a message
void atom_queue(char atom, int pid, int TI, data_t *data_ptr) {

    // increase the number of atoms queued
    data_ptr->atoms_queued += 1;

    // sleep for random time 
    random_sleep_ms(0, TI); 

    // log atom queue
    log_started_queue(atom, pid, data_ptr, 1);
}

/*
   void create_molecule(char atom, int pid, data_t *data_ptr) {
   sem_wait(sem_mol);

// pointer to variable in shared memory with the number of lines printed
int *line_num_ptr = &(data_ptr->line_num);

// pointer to variable in shared memory with the number of molecules created
int *mol_num_ptr = &(data_ptr->mol_num);

// log molecule start
log_molecule(atom, pid, mol_num_ptr);

sem_post(sem_mol);
}
*/
