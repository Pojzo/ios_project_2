#ifndef OXYGEN_H
#define OXYGEN_H
#include <semaphore.h>

void atom_process(char atom, int pid, int TI, sem_t *sem_start, int *ptr);

#endif
