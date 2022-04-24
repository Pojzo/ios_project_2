#ifndef LOGGER_H
#define LOGGER_H

#include "shared_memory.h"

void log_line(int *line_ptr);
void log_started(char atom, int atom_idx, data_t *data_ptr);
void log_started_queue(char atom, int atom_idx, data_t *data_ptr, int action);
void log_queue(char atom, int atom_idx, data_t *data_ptr);
void log_molecule_started(char atom, int atom_idx, data_t *data_ptr);
void log_molecule_created(char atom, int atom_idx, data_t *data_ptr);

void log_not_enough_two(char atom, int atom_idx, data_t *data_ptr);
void log_not_enough_one(char atom, int atom_idx, data_t *data_ptr);
#endif
