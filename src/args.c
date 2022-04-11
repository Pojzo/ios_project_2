#include "args.h"
#include <stdlib.h>

args_t *args_create(int num_oxygen_, int num_hydrogen_, int TI_, int TB_) {
    args_t *args = (args_t *) malloc(sizeof(args_t));
    if (num_oxygen_ > 0) {
        args->num_oxygen = num_oxygen_;
    }

    if (num_hydrogen_ > 0) {
        args->num_hydrogen = num_hydrogen_;
    }

    if (TI_valid_range(TI_)) {
        args->TI = TI_;
    }

    if (TB_valid_range(TB_)) {
        args->TB = TB_;
    }

    return args;
}

bool TI_valid_range(int TI) {
    return TI >= MIN_TI && TI <= MAX_TI;
}

bool TB_valid_range(int TB) {
    return TB >= MIN_TB && TB <= MAX_TB;
}
