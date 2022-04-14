#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared_memory.h"

int main(int argc, char **argv) {
    if (argc != 1) {
        printf("This program doesn't take any arguments\n");
        return -1;
    }

    if (destroy_memory_block(FILENAME)) {
        printf("Destroyed block: %s\n", FILENAME);
    }
    else {
        printf("Could not destroy block %s\n", FILENAME); 
    }

    return 0;
}
