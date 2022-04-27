#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "common.h"
#include "atom.h"

void oxygen_process(char atom, int atom_idx, data_t *data_ptr) {
    log_started(atom, atom_idx, data_ptr); 
    random_sleep_ms(0, data_ptr->args->TI); 
    log_queue(atom, atom_idx, data_ptr);
    data_ptr->cur_o = atom_idx;
    sem_wait(&data_ptr->sem_mol_oxygen); // wait for molecule to start creating
                                         // ak uz sa nema vytvorit dalsia molekula
                                         // tak ides do 
                                         //
                                         /*
    if (cur_mol == max_mol) {
        vypis not enough;
        return;
    }
    */
                                         
    log_molecule_started(atom, atom_idx, data_ptr);

    sem_post(&data_ptr->sem_mol_hydrogen); // let two hydrogen molecules start creating
    sem_post(&data_ptr->sem_mol_hydrogen); // let two hydrogen molecules start creating

    sem_wait(&data_ptr->sem_hydrogen);
    sem_wait(&data_ptr->sem_hydrogen);
    random_sleep_ms(0, data_ptr->args->TB);
    log_molecule_created_all(data_ptr);
    data_ptr->cur_o = 0;
    data_ptr->cur_h1 = 0;
    data_ptr->cur_h2 = 0;

    data_ptr->mol_num++;
    sem_post(&data_ptr->sem_mol_oxygen);
}

void hydrogen_process(char atom, int atom_idx, data_t *data_ptr) {
    log_started(atom, atom_idx, data_ptr); 
    random_sleep_ms(0, data_ptr->args->TI); 
    log_queue(atom, atom_idx, data_ptr);

    sem_wait(&data_ptr->sem_mol_hydrogen); // wait for oxygen to allow hydrogen to start creating a molecule
    log_molecule_started(atom, atom_idx, data_ptr);
    if (data_ptr->cur_h1 == 0) {
        data_ptr->cur_h1 = atom_idx;
    }
    else {
        data_ptr->cur_h2 = atom_idx;
    }
    sem_post(&data_ptr->sem_hydrogen); // let oxygen know that one hydrogen is ready
}

void bond(char atom, int atom_idx, data_t *data_ptr) {
    log_molecule_started(atom, atom_idx, data_ptr);
    random_sleep_ms(0, data_ptr->args->TB); // data_ptr->args->TB);
                                            // log_molecule_created(atom, atom_idx, data_ptr);
    sem_post(&data_ptr->barrier);
}
