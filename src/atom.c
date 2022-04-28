#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "common.h"
#include "atom.h"

void oxygen_process(char atom, int atom_idx, data_t *data_ptr, int max_mol) {
    log_started(atom, atom_idx, data_ptr); 
    random_sleep_ms(0, data_ptr->args->TI); 
    log_queue(atom, atom_idx, data_ptr);
    data_ptr->cur_o = atom_idx;
    sem_wait(&data_ptr->sem_mol_oxygen); // wait for molecule to start creating
                                         // ak uz sa nema vytvorit dalsia molekula
                                         // tak ides do 
                                         //
    if (data_ptr->mol_num > max_mol) {
        log_not_enough_one(atom, atom_idx, data_ptr);
        for (int i = max_mol * 2; i <= data_ptr->args->num_hydrogen; i++) {
            sem_post(&data_ptr->sem_mol_hydrogen);
        }
        return;
    }
                                         

    sem_post(&data_ptr->sem_mol_hydrogen); // let two hydrogen molecules start creating
    sem_post(&data_ptr->sem_mol_hydrogen); // let two hydrogen molecules start creating


    sem_wait(&data_ptr->sem_hydrogen);
    sem_wait(&data_ptr->sem_hydrogen);
    log_molecule_started(atom, atom_idx, data_ptr);
    random_sleep_ms(0, data_ptr->args->TB);
    log_molecule_created_all(data_ptr);
    data_ptr->cur_o = 0;
    data_ptr->cur_h1 = 0;
    data_ptr->cur_h2 = 0;

    data_ptr->mol_num++;
    sem_post(&data_ptr->sem_mol_oxygen);
    exit(EXIT_SUCCESS);
}

void hydrogen_process(char atom, int atom_idx, data_t *data_ptr, int max_mol) {
    log_started(atom, atom_idx, data_ptr); 
    random_sleep_ms(0, data_ptr->args->TI); 
    log_queue(atom, atom_idx, data_ptr);

    sem_wait(&data_ptr->sem_mol_hydrogen); // wait for oxygen to allow hydrogen to start creating a molecule
    if (data_ptr->mol_num > max_mol) {
        log_not_enough_two(atom, atom_idx, data_ptr);
        return;
    }


    if (data_ptr->cur_h1 == 0) {
        data_ptr->cur_h1 = atom_idx;
    }
    else {
        data_ptr->cur_h2 = atom_idx;
    }
    log_molecule_started(atom, atom_idx, data_ptr);
    sem_post(&data_ptr->sem_hydrogen); // let oxygen know that one hydrogen is ready
    exit(EXIT_SUCCESS);
}

void bond(char atom, int atom_idx, data_t *data_ptr) {
    log_molecule_started(atom, atom_idx, data_ptr);
    random_sleep_ms(0, data_ptr->args->TB); // data_ptr->args->TB);
                                            // log_molecule_created(atom, atom_idx, data_ptr);
    sem_post(&data_ptr->barrier);
}
