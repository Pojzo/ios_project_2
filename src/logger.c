#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "shared_memory.h"

const char OXYGEN_ATOM = 'O';
const char HYDROGEN_ATOM = 'H';

char *queue_msg = "%s %d\n: going to queue";
char *mollecule_msg = "%s %d: creating molecule %d\n";

// log line number
void log_line(int *line_ptr) {
    *line_ptr += 1;
    int line_num = *line_ptr;
    printf("%d: ", line_num - 1);
}

// log the message started along with corresponding atom
void log_started(char atom, int atom_idx) {
    if (atom_idx <= 0) {
        fprintf(stderr, "Atom index must be greater than zero\n");
        return;
    }

    if (atom == OXYGEN_ATOM || atom == HYDROGEN_ATOM) {
        printf("%c %d: started\n", atom, atom_idx);
        return;
    }
    fprintf(stderr, "Invalid atom to print\n");
}

// log the message going to queue along with corresponding atom
void log_queue(char atom, int atom_idx) {
    if (atom_idx <= 0) {
        fprintf(stderr, "Atom index must be greater than zero\n");
        return;
    }

    if (atom == OXYGEN_ATOM || atom == HYDROGEN_ATOM) {
        printf("%c %d: going to queue\n", atom, atom_idx);
        return;
    }
    fprintf(stderr, "Invalid atom to print\n");
}

// log the message creating molecule along with corresponding atom and molecule 
void log_molecule(char atom, int atom_idx, int *mol_num_ptr) {
    if (atom_idx <= 0) {
        fprintf(stderr, "Atom index must be greater than zero\n");
        return;
    }

    if (*mol_num_ptr <= 0) {
        fprintf(stderr, "Molecule index must be greater than zero\n");
        return;
    }

    if (atom == OXYGEN_ATOM || atom == HYDROGEN_ATOM) {
        printf("%c %d: molecule %d created\n", atom, atom_idx, *mol_num_ptr);
        *mol_num_ptr += 1;
        return;
    }
    fprintf(stderr, "Invalid atom to print\n");
}

void log_not_enough_one(char first_atom, int atom_idx, char second_atom) {
    if (atom_idx <= 0) {
        fprintf(stderr, "Atom index must be greater than zero\n");
        return;
    }
    if ((first_atom == OXYGEN_ATOM || first_atom == HYDROGEN_ATOM) &&\
        (second_atom == OXYGEN_ATOM || second_atom == HYDROGEN_ATOM)) {
        printf("%c %d: not enough %c\n", first_atom, atom_idx, second_atom);
        return;
    }
    fprintf(stderr, "Invalid atoms to print\n");
}

void log_not_enough_two(char first_atom, int atom_idx, char second_atom, char third_atom) {
    if (atom_idx <= 0) {
        fprintf(stderr, "Atom index must be greater than zero\n");
        return;
    }
    if ((first_atom == OXYGEN_ATOM || first_atom == HYDROGEN_ATOM) &&\
        (second_atom == OXYGEN_ATOM || second_atom == HYDROGEN_ATOM) &&\
        (third_atom == OXYGEN_ATOM || third_atom == HYDROGEN_ATOM)) {

        printf("%c %d: not enough %c or %c\n", first_atom, atom_idx, second_atom, third_atom);
        return;
    }
    fprintf(stderr, "Invalid atoms to print\n");
}
