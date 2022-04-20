#define _GNU_SOURCE

#include <sys/mman.h>
#include "shared_memory.h"
#include "common.h"
#include <fcntl.h>

const int n = 1;

// data_t constructor
data_t *data_create() {
    data_t *data = mmap (NULL, n * sizeof(int),
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);

    // data_t *data = (data_t *) malloc(sizeof(data_t));

    if (data == NULL) {
        return data;
    }
    data->line_num = 1;
    data->mol_num = 1;
    data->atoms_started = 0;
    data->atoms_queued = 0;

    sem_t *sem_start = sem_open(sem_start_name, O_CREAT, 0600, 0);
    sem_t *sem_print = sem_open(sem_print_name, O_CREAT, 0600, 0);

    if (sem_start == NULL || sem_print == NULL) {
        fprintf(stderr, "Couldn't create semaphores\n"); 
        return NULL;
    }

    data->sem_start = sem_start;
    data->sem_print = sem_print;

    sem_post(sem_start);
    sem_post(sem_print);

    return data;
}

// data_t destructor
void data_free(data_t *data) {
    // close all semaphores
    sem_close(data->sem_start);
    sem_close(data->sem_print);

    // free all semaphores
    free(data->sem_start);
    free(data->sem_print);

    // free pointer to data stuct
    free(data); 
}
