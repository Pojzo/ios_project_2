#define _GNU_SOURCE

#include <sys/mman.h>
#include "shared_memory.h"
#include "common.h"

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

    return data;
}

// data_t destructor
void data_free(data_t *data) {
    free(data); 
}
