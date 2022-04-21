#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "common.h"
#include "atom.h"

void atom_process(char atom, int pid, int TI, data_t *data_ptr) {
    srand(getpid());
    atom_start(atom, pid, data_ptr);
    random_sleep_ms(0, TI); 
    atom_queue(atom, pid, TI, data_ptr);
    (void) TI;
    // create_molecule(atom, pid, sem_mol, data_ptr);
}


// start atom process and log a message
void atom_start(char atom, int pid, data_t *data_ptr) {
    if (atom == 'O') {
        sem_wait(&(data_ptr->sem_oxygen));

        sem_wait(&(data_ptr->sem_print));
        //log_started_queue(atom, pid, data_ptr, 0); 

        int value = data_ptr->line_num;
        printf("TOTO JE PRED TY KOKOT SKURVENY: %d\n", value);
        printf("%d: %c %d: started\n", ++(data_ptr->line_num), atom, pid);
        value = data_ptr->line_num;
        printf("TOTO JE PO TY KOKOT VYJEBANY: %d\n", value);
        fflush(stdout);
        sem_post(&(data_ptr->sem_print));
        sem_post(&(data_ptr->sem_oxygen));
    }
    else {
        sem_wait(&(data_ptr->sem_hydrogen));
        sem_wait(&(data_ptr->sem_print));

        printf("%d: %c %d: started\n", ++data_ptr->line_num, atom, pid);
        fflush(stdout);
        // log_started_queue(atom, pid, data_ptr, 0);

        sem_post(&(data_ptr->sem_print));
        sem_post(&(data_ptr->sem_hydrogen));
    }
}

// add atom to queue and log a message
void atom_queue(char atom, int pid, int TI, data_t *data_ptr) {
    (void) TI;
    if (atom == 'O') {
        sem_wait(&(data_ptr->sem_print));
        //log_started_queue(atom, pid, data_ptr, 0); 

        printf("%d: %c %d: going to queue\n", data_ptr->line_num++, atom, pid);
        fflush(stdout);
        sem_post(&(data_ptr->sem_print));
    }
    else {
        sem_wait(&(data_ptr->sem_print));

        printf("%d: %c %d: going to queue\n", data_ptr->line_num++, atom, pid);
        fflush(stdout);
        // log_started_queue(atom, pid, data_ptr, 0);

        sem_post(&(data_ptr->sem_print));
    }

    // sleep for random time 

    // log atom queue
    // log_started_queue(atom, pid, data_ptr, 1);
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
