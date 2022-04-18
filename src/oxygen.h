#ifndef OXYGEN_H
#define OXYGEN_H
#include <semaphore.h>

void oxygen_process(int pid, int TI, sem_t *sem_start);

#endif
