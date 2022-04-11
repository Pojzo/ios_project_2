#include <stdbool.h>
#include <stdio.h>

bool is_numeric(const char *str) 
{
    while(*str != '\0')
    {
        if(*str < '0' || *str > '9')
            return false;
        str++;
    }
    return true;
}

void print_usage() {
    printf("Usage: ./proj2 NO NB TI<0, 1000> TB<0, 1000>\n");
}

