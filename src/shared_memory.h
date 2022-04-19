#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

typedef struct  {
    int line_num;
    int mol_num;
    int atoms_started;
    int atoms_queued;
} data_t;

data_t *data_create();
void data_free(data_t *data);
int *get_ptr();

#endif
