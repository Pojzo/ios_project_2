#include <sys/types.h>
#include "utils.h"
#include "logger.h"
#include "common.h"
#include "atom.h"

void oxygen_process(char atom, int atom_idx, data_t *data_ptr) {
    log_started(atom, atom_idx, data_ptr); 
    random_sleep_ms(0, data_ptr->args->TI); 
    log_queue(atom, atom_idx, data_ptr);
    data_ptr->num_queued_o += 1;

    sem_wait(&data_ptr->sem_mol);
    data_ptr->num_oxygen += 1;
    if (data_ptr->num_hydrogen >= 2) {
        sem_post(&data_ptr->sem_hydrogen);
        sem_post(&data_ptr->sem_hydrogen);
        data_ptr->num_hydrogen -= 2;

        sem_post(&data_ptr->sem_oxygen);
        data_ptr->num_oxygen -= 1;
        // random_sleep_ms(0, data_ptr->args->TB);
    }
    else {
        sem_post(&data_ptr->sem_mol);
    }

    sem_wait(&data_ptr->sem_oxygen);

    data_ptr->cur_o = atom_idx;
    bond(atom, atom_idx, data_ptr);

    //log_molecule_created(atom, atom_idx, data_ptr);

    sem_wait(&data_ptr->barrier);
    sem_post(&data_ptr->sem_mol);
    log_molecule_created_all(data_ptr);
    data_ptr->mol_num++;

    if (data_ptr->args->num_hydrogen - data_ptr->num_queued_h < 2) {
        log_not_enough_one(atom, atom_idx, data_ptr);
        return;
    }
}

void hydrogen_process(char atom, int atom_idx, data_t *data_ptr) {
    log_started(atom, atom_idx, data_ptr); 
    random_sleep_ms(0, data_ptr->args->TI); 
    log_queue(atom, atom_idx, data_ptr);
    data_ptr->num_queued_h++;
    sem_wait(&data_ptr->sem_mol);
    data_ptr->num_hydrogen += 1;
    if (data_ptr->num_hydrogen >= 2 && data_ptr->num_oxygen >= 1) {
        sem_post(&data_ptr->sem_hydrogen);
        sem_post(&data_ptr->sem_hydrogen);
        data_ptr->num_hydrogen -= 2;

        sem_post(&data_ptr->sem_oxygen);
        data_ptr->num_oxygen -= 1;
    }
    else {
        sem_post(&data_ptr->sem_mol);
    }
    if (data_ptr->args->num_hydrogen - data_ptr->num_queued_h < 2) {
        log_not_enough_two(atom, atom_idx, data_ptr);
        return;
    }


    sem_wait(&data_ptr->sem_hydrogen);
    if (data_ptr->cur_h1 == 0) {
        data_ptr->cur_h1 = atom_idx; 
    }
    else {
        data_ptr->cur_h2 = atom_idx;
    }
    bond(atom, atom_idx, data_ptr);

    sem_wait(&data_ptr->barrier);
}

void bond(char atom, int atom_idx, data_t *data_ptr) {
    log_molecule_started(atom, atom_idx, data_ptr);
    random_sleep_ms(0, data_ptr->args->TB); // data_ptr->args->TB);
                                            // log_molecule_created(atom, atom_idx, data_ptr);
    sem_post(&data_ptr->barrier);
}
