#ifndef OXYGEN_H
#define OXYGEN_H
#include <semaphore.h>
#include "shared_memory.h"

void atom_process(char atom, int pid, int TI, data_t *data_ptr);
void atom_start(char atom, int pid, data_t *data_ptr);
void atom_queue(char atom, int pid, int IT, data_t *data_ptr);
void create_molecule(char atom, int pid, data_t *data_ptr);
#endif
