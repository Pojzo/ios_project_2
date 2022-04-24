#ifndef ARGUMENTS_H
#define ARGUMENTS_H


#include <stdbool.h>

typedef struct {
    int num_oxygen;
    int num_hydrogen;
    int TI;
    int TB;
} args_t;

args_t *args_create(const char *num_oxygen_, const char *num_hydrogen_, const char *TI_, const char *TB_);
bool args_valid(const char *num_oxygen_, const char *num_hydrogen_, const char *TI_, const char *TB_);
bool args_in_range(const char *num_oxygen_, const char *num_hydrogen_, const char *TI_, const char *TB_);
bool TI_valid_range(int TI);
bool TB_valid_range(int TB);
void args_print(args_t *args);
void args_free(args_t *args);

#endif
