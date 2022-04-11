#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "utils.h"

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }
    args_t *args = args_create(argv[1], argv[2], argv[3], argv[4]);
    if (args == NULL) {
        return 1;
    }
    print_args(args);

    return 0;
}
