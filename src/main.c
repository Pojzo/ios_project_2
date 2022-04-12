#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "utils.h"

static const int NUM_ARGS = 5;

int main(int argc, char **argv) {
    if (argc != NUM_ARGS) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    printf("Output funkcie args_valid: %d\n", args_valid(argv[1], argv[2], argv[3], argv[4]));

    args_t *args = args_create(argv[1], argv[2], argv[3], argv[4]);
    if (args == NULL) {
        return 1;
    }
    args_print(args);

    args_free(args);
    printf("Output funkcie args_valid: %d\n", args_valid(argv[1], argv[2], argv[3], argv[4]));

    return 0;
}
