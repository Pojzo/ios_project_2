#include "common.h"
#include "logger.h"
#include <semaphore.h>
#include "shared_memory.h"

const char OXYGEN_ATOM = 'O';
const char HYDROGEN_ATOM = 'H';

char *queue_msg = "%s %d\n: going to queue";
char *mollecule_msg = "%s %d: creating molecule %d\n";


// log line number
// log the message started along with corresponding atom
void log_started(char atom, int atom_idx, data_t *data_ptr) {
    sem_wait(&(data_ptr->sem_print));
    int value;
    sem_getvalue(&(data_ptr->sem_print), &value);
    fprintf(data_ptr->fp, "%d: %c %d: started\n", data_ptr->line_num++, atom, atom_idx);
    fflush(data_ptr->fp);
    sem_post(&(data_ptr->sem_print));
}

void log_started_queue(char atom, int atom_idx, data_t *data_ptr, int action) {
    printf("Tu som sa dostal more\n");
    sem_wait(&(data_ptr->sem_print));
    if (action == 0) {
        printf("%d: %c %d: started\n", data_ptr->line_num++, atom, atom_idx);
        fflush(data_ptr->fp);
    }
    else if (action == 1) {

        printf("%d: %c %d: going to queue\n", data_ptr->line_num++, atom, atom_idx);
        fflush(data_ptr->fp);
    }
    sem_post(&(data_ptr->sem_print));
}

// log the message going to queue along with corresponding atom
void log_queue(char atom, int atom_idx, data_t *data_ptr) {
    sem_wait(&(data_ptr->sem_print));
    int value;
    sem_getvalue(&(data_ptr->sem_print), &value);
    fprintf(data_ptr->fp, "%d: %c %d: going to queue\n", data_ptr->line_num++, atom, atom_idx);
    fflush(data_ptr->fp);
    sem_post(&(data_ptr->sem_print));
}

// log the message creating molecule along with corresponding atom and molecule 
void log_molecule_started(char atom, int atom_idx, data_t *data_ptr) { 
    sem_wait(&data_ptr->sem_print);
    fprintf(data_ptr->fp, "%d: %c %d: creating molecule %d\n", data_ptr->line_num++, atom, atom_idx, data_ptr->mol_num);
    fflush(data_ptr->fp);
    sem_post(&data_ptr->sem_print);
}

void log_molecule_created(char atom, int atom_idx, data_t *data_ptr) { 
    sem_wait(&data_ptr->sem_print);
    printf("%d: %c %d: molecule %d created\n", data_ptr->line_num++, atom, atom_idx, data_ptr->mol_num);
    fflush(data_ptr->fp);
    sem_post(&data_ptr->sem_print);
}

void log_molecule_created_all(data_t *data_ptr) {
    sem_wait(&data_ptr->sem_print);
    fprintf(data_ptr->fp, "%d: %c %d: molecule %d created\n", data_ptr->line_num++, 'O', data_ptr->cur_o, data_ptr->mol_num);
    fprintf(data_ptr->fp, "%d: %c %d: molecule %d created\n", data_ptr->line_num++, 'H', data_ptr->cur_h1, data_ptr->mol_num);
    fprintf(data_ptr->fp, "%d: %c %d: molecule %d created\n", data_ptr->line_num++, 'H', data_ptr->cur_h2, data_ptr->mol_num);
    fflush(data_ptr->fp);
    data_ptr->cur_o = 0;
    data_ptr->cur_h1 = 0;
    data_ptr->cur_h2 = 0;
    sem_post(&data_ptr->sem_print);
}

void log_not_enough_two(char atom, int atom_idx, data_t *data_ptr) {
    sem_wait(&(data_ptr->sem_print));
    fprintf(data_ptr->fp, "%d: %c %d: not enough O or H\n", data_ptr->line_num++, atom, atom_idx);
    fflush(data_ptr->fp);
    sem_post(&(data_ptr->sem_print));
}

void log_not_enough_one(char atom, int atom_idx, data_t *data_ptr) {
    sem_wait(&(data_ptr->sem_print));
    fprintf(data_ptr->fp, "%d: %c %d: not enough H\n", data_ptr->line_num++, atom, atom_idx);
    fflush(data_ptr->fp);
    sem_post(&(data_ptr->sem_print));
}
