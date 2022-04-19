#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

typedef struct  {
    int line_num;
} data_t;

data_t *data_create();
void data_free(data_t *data);
int *get_ptr();

#endif
