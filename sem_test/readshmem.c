#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/ipc.h>

#include "shared_memory.h"

#define BLOCK_SIZE 4096

int main(int argc, char **argv) {
    if (argc != 1) {
        printf("This program doesn't take any arguments\n");
        return -1;
    }

    sem_unlink(SEM_CONSUMER_FNAME);
    sem_unlink(SEM_PRODUCER_FNAME);
    
    sem_t *sem_prod = sem_open(SEM_PRODUCER_FNAME, IPC_CREAT, 0660, 0);
    if (sem_prod == SEM_FAILED) {
        perror("sem_open/producer");
        exit(EXIT_FAILURE);
    }

    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        printf("ERROR: couldn't get block\n");
        return -1;
    }
    while (true) {  
        if (strlen(block) > 0) {
            printf("Reading: %s\n\n", block);
            bool done = (strcmp(block, "quit") == 0);
            block[0] = 0;
            if (done) {
                break;
            }
        }
    }
    return 0;
}
