#ifndef LOGGER_H
#define LOGGER_H

void log_line(int *line_ptr);
void log_started(char atom, int atom_idx);
void log_queue(char atom, int atom_idx);
void log_molecule(char atom, int atom_idx, int *mol_num_ptr);
void log_not_enough_one(char atom, int atom_idx, char second_atom);
void log_not_enough_two(char atom, int atom_idx, char second_atom, char third_atom);

#endif
