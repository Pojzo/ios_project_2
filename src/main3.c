#include <sys/wait.h>
/*
#include "args.h"
#include "utils.h"
#include "common.h"
#include "shared_memory.h"
#include "atom.h"
#include "logger.h"

void mol_process(sem_t *sem_mol, int num_oxygen, int num_hydrogen, data_t *data_ptr);

void oxygen(int atom_idx, int TI);
void hydrogen(int atom_idx, int TI);

static const int NUM_ARGS = 5;
int oxygen_id = 0;
int hydrogen_id = 0;

data_t *data_ptr; 
int main(int argc, char **argv) {
    data_ptr = data_create();
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
            data_free(data_ptr);
            exit(EXIT_FAILURE);
        }
        oxygen_id++;
        if (pid == 0) {
            oxygen(oxygen_id, args->TI);
            exit(EXIT_SUCCESS);
        }
    }
    for (unsigned int i = 0; i < args->num_hydrogen; i++) {
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
            hydrogen(hydrogen_id, args->TI);
            // atom_process('H', hydrogen_id, args->TI, data_ptr);
            exit(EXIT_SUCCESS);
        }
    }
    while(wait(NULL) > 0);
    args_free(args);
    data_free(data_ptr);
    return 0;
}

void oxygen(int atom_idx, int TI) {

    sem_wait(&data_ptr->sem_oxygen);
    sem_wait(&data_ptr->sem_print);
    printf("%d: %c %d: started\n", data_ptr->line_num++, 'O', atom_idx);
    fflush(stdout);
    sem_post(&data_ptr->sem_print);
    sem_post(&data_ptr->sem_oxygen);

    sem_wait(&data_ptr->sem_print);
    random_sleep_ms(0, TI);
    printf("%d: %c %d: going to queue\n", data_ptr->line_num++, 'O', atom_idx);
    fflush(stdout);
    sem_post(&data_ptr->sem_print);
}

void hydrogen(int atom_idx, int TI) {
    sem_wait(&data_ptr->sem_hydrogen);
    sem_wait(&data_ptr->sem_print);
    printf("%d: %c %d: started\n", data_ptr->line_num++, 'H', atom_idx);
    sem_post(&data_ptr->sem_print);
    sem_post(&data_ptr->sem_hydrogen);

    sem_wait(&data_ptr->sem_print);
    random_sleep_ms(0, TI);
    printf("%d: %c %d: going to queue\n", data_ptr->line_num++, 'H', atom_idx);
    sem_post(&data_ptr->sem_print);
}
*/
