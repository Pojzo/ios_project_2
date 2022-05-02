#include "args.h"
#include <sys/wait.h>
#include "utils.h"
#include "common.h"
#include "shared_memory.h"
#include "atom.h"
#include "logger.h"

void mol_process(sem_t *sem_mol, int num_oxygen, int num_hydrogen, data_t *data_ptr);

static const int NUM_ARGS = 5;
int oxygen_id = 0;
int hydrogen_id = 0;

int main(int argc, char **argv) {
    data_t *data_ptr  = data_create();

    if (argc != NUM_ARGS) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    args_t *args = args_create(argv[1], argv[2], argv[3], argv[4]);
    if (args == NULL) {
        return 1;
    }

    data_ptr->args = args;
    int max_mol = min(args->num_hydrogen / 2, args->num_oxygen);
    if (max_mol == 0) {
        sem_post(&data_ptr->sem_end);
    }
    // data_ptr->max_mol = max_mol;
    // printf("Max molekul: %d\n", max_mol);

    for (int i = 0; i < data_ptr->args->num_oxygen; i++) {
        pid_t pid = fork();
        // child process
        if (pid == -1) {
            fprintf(stderr, "Fork didn't work\n");
            args_free(args);
            data_free(data_ptr);
            exit(EXIT_FAILURE);
        }
        oxygen_id++;
        if (pid == 0) {
            oxygen_process('O', oxygen_id, data_ptr, max_mol);
            exit(EXIT_SUCCESS);
        }
    }
    for (int i = 0; i < data_ptr->args->num_hydrogen; i++) {
        pid_t pid = fork();
        // child process
        if (pid == -1) {
            fprintf(stderr, "Fork didn't work\n");
            args_free(args);
            data_free(data_ptr);
            exit(EXIT_FAILURE);
        }
        hydrogen_id++;
        if (pid == 0) {
            hydrogen_process('H', hydrogen_id, data_ptr, max_mol);
            exit(EXIT_SUCCESS);
        }
    }

    sem_wait(&data_ptr->sem_end);
    if (args->num_oxygen * 2 < args->num_hydrogen) {
        // printf("Je to mensie vobec more?\n");
        for (int i = max_mol * 2; i < data_ptr->args->num_hydrogen; i++) {
            sem_post(&data_ptr->sem_mol_hydrogen);
        }
        // printf("oxygen: %d, hydrogen: %d\n", args->num_oxygen, args->num_hydrogen);
        // printf("tolkotok je %d\n", max_mol);
        // printf("Tolkotok ich musim este ukoncit %d\n", data_ptr->args->num_hydrogen - max_mol * 2);
    }

    while(wait(NULL) > 0);
    args_free(args);
    data_free(data_ptr);

    return 0;
}
