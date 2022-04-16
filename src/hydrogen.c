#include <stdio.h>
#include <unistd.h>
#include "logger.h"
#include "hydrogen.h"
#include "utils.h"

static const char atom = 'H';

void hydrogen_process(int pid, int TI) {
    log_started(atom, pid);
    float queue_wait_time = rand_in_range(0, TI);
    queue_wait_time /= 1000;
    sleep(queue_wait_time);
    log_queue(atom, pid);

}
