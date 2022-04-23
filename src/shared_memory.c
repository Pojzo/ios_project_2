#define _GNU_SOURCE

#include <sys/mman.h>
#include "shared_memory.h"
#include "common.h"
#include <fcntl.h>


// data_t constructor
data_t *data_create() {
    data_t *data = mmap (NULL, sizeof(data_t),
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);

    // data_t *data = (data_t *) malloc(sizeof(data_t));

    if (data == NULL) {
        return data;
    }
    data->line_num = 1;
    data->mol_num = 1;
    data->atoms_started = 0;
    data->atoms_queued = 0;


    if (sem_init(&(data->sem_oxygen), 1, 1) == -1) {
        fprintf(stderr, "Couldn't create semaphores\n"); 
        return NULL;
    }
    if (sem_init(&(data->sem_hydrogen), 1, 1) == -1) {
        fprintf(stderr, "Couldn't create semaphores\n"); 
        return NULL;
    }

    if (sem_init(&(data->sem_print), 1, 1) == -1) {
        fprintf(stderr, "Couldn't create semaphores\n"); 
        return NULL;
    }

    /*
    data->sem_oxygen = sem_oxygen;
    data->sem_hydrogen = sem_hydrogen;
    data->sem_print = sem_print;
    */

    // sem_post(&(data->sem_oxygen));
    // sem_post(&(data->sem_hydrogen));
    // sem_post(&(data->sem_print));

    return data;
}

// data_t destructor
void data_free(data_t *data) {
    // close all semaphores
    sem_destroy(&(data->sem_oxygen));
    sem_destroy(&(data->sem_hydrogen));
    sem_destroy(&(data->sem_print));

    // free all semaphores
    // free(data->sem_oxygen);
    // free(data->sem_hydrogen);
    // free(data->sem_print);

    // free pointer to data stuct
    // free(data); 
}


