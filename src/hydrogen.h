#ifndef HYDROGEN_H
#define HYDROGEN_H
#include <semaphore.h>

void hydrogen_process(int pid, int TI, sem_t *sem_start);

#endif
