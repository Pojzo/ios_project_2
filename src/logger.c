#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

const char OXYGEN_ATOM = 'O';
const char HYDROGEN_ATOM = 'H';

char *queue_msg = "%s %d\n: going to queue";
char *mollecule_msg = "%s %d: creating molecule %d\n";


// log line number
void log_line(int line_num) {
    if (line_num <= 0) {
        fprintf(stderr, "Line number must be greater than zero\n");
        return;
    }
    printf("%d: ", line_num);
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
void log_molecule(char atom, int atom_idx, int molecule_idx) {
    if (atom_idx <= 0) {
        fprintf(stderr, "Atom index must be greater than zero\n");
        return;
    }

    if (molecule_idx <= 0) {
        fprintf(stderr, "Molecule index must be greater than zero\n");
        return;
    }

    if (atom == OXYGEN_ATOM || atom == HYDROGEN_ATOM) {
        printf("%c %d: molecule %d created\n", atom, atom_idx, molecule_idx);
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

int main() {
    char first_atom = 'H';
    char second_atom = 'O';
    int line = 1;
    int atom_num = 1;
    log_started(first_atom, line);
    log_queue(first_atom, atom_num);
    log_molecule(first_atom, atom_num, 2);
    log_not_enough_one(first_atom, atom_num, first_atom);
    log_not_enough_two(first_atom, atom_num, first_atom, second_atom);

    return 0;
}


