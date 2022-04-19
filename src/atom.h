#ifndef OXYGEN_H
#define OXYGEN_H
#include <semaphore.h>
#include "shared_memory.h"

void atom_process(char atom, int pid, int TI, sem_t *sem_start, sem_t *sem_mol, data_t *data_ptr);
void atom_start(char atom, int pid, sem_t *sem_start, int *line_num_ptr);
void atom_queue(char atom, int pid, int IT, sem_t *sem_start, int *line_num_ptr);
void create_molecule(char atom, int pid, sem_t *sem_mol, int *line_num_ptr, int *sem_molecule_num_ptr);
#endif
