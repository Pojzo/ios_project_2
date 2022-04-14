#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <semaphore.h>


#include "shared_memory.h"

#define BLOCK_SIZE 4096

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage - %s [stuff to write]", argv[0]);
        return -1;
    }
    
    sem_t *sem_cons = sem_open(SEM_CONSUMER_FNAME, IPC_CREAT, 0660, 0);
    if (sem_cons == SEM_FAILED) {
        perror("sem_open/consumer");
        exit(EXIT_FAILURE);
    }

    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        printf("ERROR: couldn't get block\n");
        return -1;
    }

    }
    for (int i = 0; i < 10; i++) {
        printf("Writing: %s\n\n", argv[1]);
        strncpy(block, argv[1], BLOCK_SIZE);
    }

    detach_memory_block(block);
    return 0;
}
