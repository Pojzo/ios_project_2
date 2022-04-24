#ifndef OXYGEN_H
#define OXYGEN_H
#include <semaphore.h>
#include "shared_memory.h"

void oxygen_process(char atom, int atom_idx, data_t *data_ptr);
void hydrogen_process(char atom, int atom_idx, data_t *data_ptr);
void bond(char atom, int atom_idx, data_t *data_ptr);
#endif
