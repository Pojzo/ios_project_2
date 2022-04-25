#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <semaphore.h>
#include "args.h"

typedef struct  {
    int line_num;
    int mol_num;
    int num_oxygen;
    int num_hydrogen;
    int num_queued_h;
    int num_queued_o;

    int cur_o;
    int cur_h1;
    int cur_h2;


    sem_t sem_oxygen;
    sem_t sem_hydrogen;
    sem_t sem_mol;
    sem_t sem_print;
    sem_t barrier;

    args_t *args;
} data_t;

data_t *data_create();
void data_free(data_t *data);

#endif
