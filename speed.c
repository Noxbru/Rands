#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "rands.h"

void calc_mean_var(double *mean, double *var, unsigned long int *data)
{
    unsigned int i;

    *mean=0;
    for(i = 0; i < 10; i++)
        *mean+=data[i];
    *mean/=10;

    *var=0;
    for(i = 0; i < 10; i++)
        *var+=(data[i]-*mean)*(data[i]-*mean);
    *var/=9;
}

int main(int argc, const char *argv[])
{
    unsigned int i,j;
    unsigned long int elapsed_time;
    unsigned long int times[10];
    double mean, var;

    struct timespec tp1, tp2;

    printf("#======================================#\n");
    printf("|    Speed tests for the generators    |\n");
    printf("#======================================#\n");
    printf("#======================================#\n");
    printf("| The tests consists in measuring the  |\n");
    printf("| time it takes to each generator to   |\n");
    printf("| generate 10 million random numbers   |\n");
    printf("|                                      |\n");
    printf("+--------------------------------------+\n");
    printf("| 32 Bits                              |\n");
    printf("+--------------------------------------+\n");

#if ISAAC_RAND || RANDS_USE_ALL
    isaac_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 10000000; i++)
            isaac_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| ISAAC:               %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if ISAAC_X64_RAND || RANDS_USE_ALL
    isaac_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 5000000; i++)
            isaac_x64_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| ISAAC (64bits):      %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if PR_RAND || RANDS_USE_ALL
    pr_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 10000000; i++)
            pr_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Parisi-Rapuano:      %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if __SSE2__
#if PR_SSE_RAND || RANDS_USE_ALL
    pr_sse_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 10000000; i++)
            pr_sse_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Parisi-Rapuano SSE:  %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif
#endif

    srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 10000000; i++)
            rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Rand (stdlib):       %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);

#if MT_RAND || RANDS_USE_ALL
    mt_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 10000000; i++)
            mt_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Mersenne Twister:    %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if WELL_RAND || RANDS_USE_ALL
    well_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 10000000; i++)
            well_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| WELL512:             %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if WELL_X64_RAND || RANDS_USE_ALL
    well_x64_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 5000000; i++)
            well_x64_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| WELL512 (64bits):    %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if XOR_RAND || RANDS_USE_ALL
    xor_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 10000000; i++)
            xor_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Xorshift:            %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

    // END OF 32 BITS
    
    printf("+--------------------------------------+\n");
    printf("+--------------------------------------+\n");
    printf("| 64 Bits                              |\n");
    printf("+--------------------------------------+\n");

#if ISAAC_RAND || RANDS_USE_ALL
    isaac_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 20000000; i++)
            isaac_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| ISAAC:               %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if ISAAC_X64_RAND || RANDS_USE_ALL
    isaac_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 10000000; i++)
            isaac_x64_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| ISAAC (64bits):      %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if PR_RAND || RANDS_USE_ALL
    pr_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 20000000; i++)
            pr_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Parisi-Rapuano:      %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if __SSE2__
#if PR_SSE_RAND || RANDS_USE_ALL
    pr_sse_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 20000000; i++)
            pr_sse_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Parisi-Rapuano SSE:  %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif
#endif

    srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 20000000; i++)
            rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Rand (stdlib):       %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);

#if MT_RAND || RANDS_USE_ALL
    mt_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 20000000; i++)
            mt_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Mersenne Twister:    %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if WELL_RAND || RANDS_USE_ALL
    well_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 20000000; i++)
            well_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| WELL512:             %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if WELL_X64_RAND || RANDS_USE_ALL
    well_x64_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 10000000; i++)
            well_x64_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| WELL512 (64bits):    %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

#if XOR_RAND || RANDS_USE_ALL
    xor_srand(time(NULL));
    for(j = 0; j < 10; j++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tp1);
        for(i = 0; i < 20000000; i++)
            xor_rand();
        clock_gettime(CLOCK_MONOTONIC,&tp2);
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec;
        times[j] = elapsed_time;
    }
    calc_mean_var(&mean,&var,times);

    printf("| Xorshift:            %.4lf ± %.4lf |\n",mean/1e9, sqrt(var)/1e9);
#endif

    // END OF 64 BITS

    printf("+--------------------------------------+\n");
    
    return 0;
}
