#include <fcntl.h>
#include <sys/types.h>
#include "args.h"
#include "utils.h"
#include "common.h"
#include "shared_memory.h"
#include "atom.h"

void mol_process(sem_t *sem_mol, int num_oxygen, int num_hydrogen, data_t *data_ptr);

static const int NUM_ARGS = 5;
int oxygen_id = 0;
int hydrogen_id = 0;

const char *sem_oxygen_start_name = "oxygen_start";
const char *sem_hydrogen_start_name = "hydrogen_start";
const char *sem_mol_name = "molecule_start";
const char *sem_oxygen_queue_name = "oxygen_queue";
const char *sem_hydrogen_queue_name = "oxygen_queue";

int main(int argc, char **argv) {
    data_t *data_ptr  = data_create();
    sem_t *sem_oxygen_start = sem_open(sem_oxygen_start_name, O_CREAT, 0600, 0);
    sem_t *sem_hydrogen_start = sem_open(sem_hydrogen_start_name, O_CREAT, 0600, 0);
    sem_t *sem_mol = sem_open(sem_mol_name, O_CREAT, 0600, 0);

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
            atom_process('O', oxygen_id, args->TI, sem_oxygen_start, sem_mol, data_ptr);
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
            atom_process('H', hydrogen_id, args->TI, sem_hydrogen_start, sem_mol, data_ptr);
            exit(0);
        }
    }
    // process for creating molecules
    pid_t pid = fork();
    if (pid == 0) {
        mol_process(sem_mol, args->num_oxygen, args->num_hydrogen, data_ptr);
    }

    sem_close(sem_oxygen_start);
    sem_close(sem_hydrogen_start);
    sem_close(sem_mol);
    args_free(args);
    return 0;
}

void mol_process(sem_t *sem_mol, int num_oxygen, int num_hydrogen, data_t *data_ptr) {
    while (true) {
        if (data_ptr->atoms_queued == num_oxygen + num_hydrogen) {
            sem_post(sem_mol);
            printf("All molecules queued\n");
            exit(0);
        }
    }
}
