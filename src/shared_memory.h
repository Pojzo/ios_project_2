#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <semaphore.h>

typedef struct  {
    int line_num;
    int mol_num;
    int num_oxygen;
    int num_hydrogen;

    sem_t sem_oxygen;
    sem_t sem_hydrogen;
    sem_t sem_mol;
    sem_t sem_print;
} data_t;

data_t *data_create();
void data_free(data_t *data);

#endif
