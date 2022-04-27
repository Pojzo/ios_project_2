#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// return true if argument str is numeric
bool is_numeric(const char *str) 
{
    while(*str != '\0') {
        if(*str < '0' || *str > '9')
            return false;
        str++;
    }
    return true;
}

// print usage for proj2
void print_usage() {
    printf("Usage: ./proj2 NO NB TI<0, 1000> TB<0, 1000>\n");
}

// return random number in range start - end
int rand_in_range(int start, int end) {
    if (end <= start) {
        fprintf(stderr, "End must be greater than start\n");
        return -1;
    }

    int num = (rand() %
            (end - start + 1)) + start;

    return num;
}

// wait for delay miliseconds
void random_sleep_ms(int start, int end) {
    float sleep_time = rand_in_range(start, end);

    (void) sleep_time;
    // convert to miliseconds
    // usleep(sleep_time * 1000);
}

int min(int first, int second) {
    if (first < second) {
        return first;
    }
    return second;
}
