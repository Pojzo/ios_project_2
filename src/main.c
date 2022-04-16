#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "args.h"
#include "utils.h"
#include "oxygen.h"
#include "hydrogen.h"

static const int NUM_ARGS = 5;
int oxygen_id = 0;
int hydrogen_id = 0;

int main(int argc, char **argv) {
    if (argc != NUM_ARGS) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    args_t *args = args_create(argv[1], argv[2], argv[3], argv[4]);
    if (args == NULL) {
        return 1;
    }

    for (unsigned i = 0; i < args->num_oxygen; i++) {
        pid_t pid = fork();
        // child process
        if (pid == -1) {
            fprintf(stderr, "Fork didn't work\n");
            args_free(args);
            return 1;
        }
        oxygen_id++;
        if (pid == 0) {
            oxygen_process(oxygen_id, args->TI);
            exit(0);
        }
    }
    for (unsigned i = 0; i < args->num_hydrogen; i++) {
        pid_t pid = fork();
        // child process
        if (pid == -1) {
            fprintf(stderr, "Fork didn't work\n");
            args_free(args);
            return 1;
        }
        hydrogen_id++;
        if (pid == 0) {
            hydrogen_process(hydrogen_id, args->TI);
            break;
        }
    }

    args_free(args);
    return 0;
}
