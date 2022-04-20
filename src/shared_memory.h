#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <semaphore.h>

typedef struct  {
    int line_num;
    int mol_num;
    int atoms_started;
    int atoms_queued;
    sem_t *sem_start;
    sem_t *sem_print;
} data_t;

data_t *data_create();
void data_free(data_t *data);
int *get_ptr();

#endif
