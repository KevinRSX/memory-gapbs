#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "../include/magicops.h"

#define WS_SIZE (3UL << 30)

unsigned long get_random_addr(void)
{
    double frac;
    unsigned long ret;

    do {
        frac = (double)rand() / RAND_MAX;
        ret = (unsigned long)(frac * WS_SIZE);
    } while (ret >= WS_SIZE);

    assert(ret < WS_SIZE && ret >= 0);
    return ret;
}

int main(void)
{
    char *buf = malloc(WS_SIZE);
    time_t t;
    unsigned long i;

    if (!buf) {
        perror("malloc");
        exit(-1);
    }

    printf("Touching all pages...\n");
    for (i = 0; i < WS_SIZE; i += 4096) {
        buf[i] = 'A';
    }

    printf("Randomly accessing all pages...\n");
    srand((unsigned)time(&t));

    zsim_magic_op_start_sim();
    // for (i = 0; i < WS_SIZE; i += 1024) {
    while (1) {
        buf[get_random_addr()] = 'B';
    }
    zsim_magic_op_end_sim();
    return 0;
}