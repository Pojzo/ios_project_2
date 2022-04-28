#define _GNU_SOURCE

#include <sys/mman.h>
#include "shared_memory.h"
#include "common.h"
#include <fcntl.h>

const char *file_name = "proj2.out";


// data_t constructor
data_t *data_create() {
    data_t *data = mmap (NULL, sizeof(data_t),
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);

    // data_t *data = (data_t *) malloc(sizeof(data_t));

    if (data == NULL) {
        return data;
    }
    
    data->fp = fopen(file_name, "w");

    data->line_num = 1;
    data->mol_num = 1;
    data->num_oxygen = 0;
    data->num_hydrogen = 0;


    if (sem_init(&(data->sem_oxygen), 1, 0) == -1) {
        fprintf(stderr, "Couldn't create oxygen semaphores\n"); 
        return NULL;
    }

    if (sem_init(&(data->sem_hydrogen), 1, 0) == -1) {
        fprintf(stderr, "Couldn't create hydrogen semaphores\n"); 
        return NULL;
    }

    if (sem_init(&(data->sem_print), 1, 1) == -1) {
        fprintf(stderr, "Couldn't create print semaphores\n"); 
        return NULL;
    }

    if (sem_init(&(data->sem_mol_oxygen), 1, 1) == -1) {
        fprintf(stderr, "Couldn't create molecule semaphores\n"); 
        return NULL;
    }

    if (sem_init(&(data->sem_mol_hydrogen), 1, 0) == -1) {
        fprintf(stderr, "Couldn't create molecule semaphores\n"); 
        return NULL;
    }

    if (sem_init(&(data->barrier), 1, 3) == -1) {
        fprintf(stderr, "Couldn't create molecule semaphores\n"); 
        return NULL;
    }

    return data;
}

// data_t destructor
void data_free(data_t *data) {
    // close all semaphores
    sem_destroy(&(data->sem_oxygen));
    sem_destroy(&(data->sem_hydrogen));
    sem_destroy(&(data->sem_print));
    sem_destroy(&(data->sem_mol_oxygen));
    sem_destroy(&(data->sem_mol_hydrogen));
    sem_destroy(&(data->barrier));
    // fclose(data->fp);

    // free all semaphores
    // free(data->sem_oxygen);
    // free(data->sem_hydrogen);
    // free(data->sem_print);

    // free pointer to data stuct
    // free(data); 
}
