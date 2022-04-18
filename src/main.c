#include <fcntl.h>
#include <sys/types.h>
#include "args.h"
#include "utils.h"
#include "oxygen.h"
#include "hydrogen.h"
#include "common.h"

static const int NUM_ARGS = 5;
int oxygen_id = 0;
int hydrogen_id = 0;

const char *sem_oxygen_start_name = "oxygen_start";
const char *sem_hydrogen_start_name = "hydrogen_start";
const char *sem_oxygen_queue_name = "oxygen_queue";
const char *sem_hydrogen_queue_name = "oxygen_queue";

int main(int argc, char **argv) {
    sem_t *sem_oxygen_start = sem_open(sem_oxygen_start_name, O_CREAT, 0600, 0);
    sem_t *sem_hydrogen_start = sem_open(sem_hydrogen_start_name, O_CREAT, 0600, 0);

    // 1 
    sem_post(sem_oxygen_start);
    sem_post(sem_hydrogen_start);

    if (argc != NUM_ARGS) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    args_t *args = args_create(argv[1], argv[2], argv[3], argv[4]);
    if (args == NULL) {
        return 1;
    }

    for (unsigned int i = 0; i < args->num_oxygen; i++) {
        pid_t pid = fork();
        // child process
        if (pid == -1) {
            fprintf(stderr, "Fork didn't work\n");
            args_free(args);
            return 1;
        }
        oxygen_id++;
        if (pid == 0) {
            oxygen_process(oxygen_id, args->TI, sem_oxygen_start);
            exit(0);
        }
    }
    for (unsigned int i = 0; i < args->num_hydrogen; i++) {
        pid_t pid = fork();
        // child process
        if (pid == -1) {
            fprintf(stderr, "Fork didn't work\n");
            args_free(args);
            return 1;
        }
        hydrogen_id++;
        if (pid == 0) {
            hydrogen_process(hydrogen_id, args->TI, sem_hydrogen_start);
            break;
        }
    }

    sem_close(sem_oxygen_start);
    sem_close(sem_hydrogen_start);
    args_free(args);
    return 0;
}
