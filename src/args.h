#ifndef ARGUMENTS_H
#define ARGUMENTS_H


#include <stdbool.h>

typedef struct {
    unsigned int num_oxygen;
    unsigned int num_hydrogen;
    unsigned int TI;
    unsigned int TB;
} args_t;

args_t *args_create(const char *num_oxygen_, const char *num_hydrogen_, const char *TI_, const char *TB_);
bool valid_args(const char *num_oxygen_, const char *num_hydrogen_, const char *TI_, const char *TB_);
bool TI_valid_range(int TI);
bool TB_valid_range(int TB);
void print_args(args_t *args);

#endif