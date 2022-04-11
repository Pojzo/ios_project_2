#include "args.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

const int MIN_TB = 0;
const int MAX_TB = 1000;

const int MIN_TI = 0;
const int MAX_TI = 1000;

args_t *args_create(const char *num_oxygen_, const char *num_hydrogen_, const char *TI_, const char *TB_) {
    args_t *args = (args_t *) malloc(sizeof(args_t));
    if (!valid_args(num_oxygen_, num_hydrogen_, TI_, TB_)) {
        print_usage();
        free(args);
        return NULL;
    }

    if (atoi(num_oxygen_) > 0) {
        args->num_oxygen = atoi(num_oxygen_);
    }

    if (atoi(num_hydrogen_) > 0) {
        args->num_hydrogen = atoi(num_hydrogen_);
    }

    if (TI_valid_range(atoi(TI_))) {
        args->TI = atoi(TI_);
    }

    if (TB_valid_range(atoi(TB_))) {
        args->TB = atoi(TB_);
    }

    return args;
}

// each argument has to be a number
bool valid_args(const char *num_oxygen, const char *num_hydrogen, const char *TI, const char *TB) {
    if (!is_numeric(num_oxygen)) {
        fprintf(stderr, "NO argument is not valid\n");
        return false;
    }

    if (!is_numeric(num_hydrogen)) {
        fprintf(stderr, "NH argument is not valid\n");
        return false;
    }

    if (!is_numeric(TI)) {
        fprintf(stderr, "TI argument is not valid\n");
        return false;
    }

    if (!is_numeric(TB)) {
        fprintf(stderr, "TB argument is not valid\n");
        return false;
    }
    return true;
}


bool TI_valid_range(int TI) {
    return TI >= MIN_TI && TI <= MAX_TI;
}

bool TB_valid_range(int TB) {
    return TB >= MIN_TB && TB <= MAX_TB;
}

void print_args(args_t *args) {
    printf("Number of oxygen atoms: %u\n", args->num_oxygen);
    printf("Number of hydrogen atoms: %u\n", args->num_hydrogen);
    printf("TI: %u\n", args->TI);
    printf("TB: %u\n", args->TB);
}
