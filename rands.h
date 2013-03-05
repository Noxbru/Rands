#ifndef RANDS
#define RANDS

#include "rands_config.h"

#if PR_RAND || RANDS_USE_ALL

#include <stdlib.h>
#include <limits.h>

typedef struct _pr_state
{
    unsigned int wheel[256];
    unsigned char index;
} pr_state;

extern pr_state pr_default_state;

void pr_srand(unsigned long int seed);
unsigned int pr_rand();

#if RANDS_USE_STATES
void pr_init_st(pr_state **st);
void pr_clear_st(pr_state *st);
void pr_srand_st(pr_state *st, unsigned long int seed);
unsigned int pr_rand_st(pr_state *st);
#endif

#endif // PR_RAND

#if WELL_RAND || RANDS_USE_ALL

typedef struct _well_state 
{
    unsigned int wheel[16];
    unsigned char index;
} well_state;

extern well_state well_default_state;

void well_srand(unsigned long seed);
unsigned int well_rand();

#if RANDS_USE_STATES
void well_init_st(well_state **st);
void well_clear_st(well_state *st);
void well_srand_st(well_state *st, unsigned long seed);
unsigned int well_rand_st(well_state *st);
#endif

#endif // WELL_RAND

#if WELL_X64_RAND || RANDS_USE_ALL

typedef struct _well_x64_state 
{
    unsigned long wheel[16];
    unsigned char index;
} well_x64_state;

extern well_x64_state well_x64_default_state;

void well_x64_srand(unsigned long seed);
unsigned long int well_x64_rand();

#if RANDS_USE_STATES
void well_x64_init_st(well_x64_state **st);
void well_x64_clear_st(well_x64_state *st);
void well_x64_srand_st(well_x64_state *st, unsigned long seed);
unsigned long int well_x64_rand_st(well_x64_state *st);
#endif

#endif // WELL_X64_RAND

#endif
