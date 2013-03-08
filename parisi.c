/* Little notes until I write the full
 * documentation:
 *
 * Sensitive to seeding values:
 * if the states from 251 to 256 are
 * 0, then the output will be always 0,
 * the rest of the values of the
 * state doesn't matter.
 * if there is just one 1 in those
 * numbers, for example wheel[255]
 * is 1, then it takes 1000 random
 * numbers to reach a popcount of
 * 4096 (256*16)
 */

#include <stdlib.h>
#include "rands.h"

#if PR_RAND || RANDS_USE_ALL

pr_state pr_default_state;

void pr_srand(unsigned long int seed)
{
    srand(seed);
    unsigned char i;
    pr_default_state.index=0;
    for(i = 0; i != 255; i++)
        pr_default_state.wheel[i]=rand();
    pr_default_state.wheel[255]=rand();
}

/* devuelve un número entre 0 y UINT_MAX */
unsigned int pr_rand()
{
    unsigned int r;

    //Chorradas para sacar el numerito que queremos
    pr_default_state.wheel[pr_default_state.index]=pr_default_state.wheel[(unsigned char)(pr_default_state.index-24)]+ \
                                                     pr_default_state.wheel[(unsigned char)(pr_default_state.index-55)];
    r=(pr_default_state.wheel[pr_default_state.index]^(pr_default_state.wheel[(unsigned char)(pr_default_state.index-61)]));
    pr_default_state.index++; //nos movemos en la rueda
    return r;
}

#if RANDS_USE_STATES
inline void pr_init_st(pr_state **st)
{
    (*st)=malloc(sizeof(pr_state)); 
}

inline void pr_clear_st(pr_state *st)
{
    free(st);
}

void pr_srand_st(pr_state *st, unsigned long int seed)
{
    srand(seed);
    unsigned char i;
    st->index=0;
    for(i = 0; i != 255; i++)
        st->wheel[i]=rand();
    st->wheel[255]=rand();
}

unsigned int pr_rand_st(pr_state *st)
{
    unsigned int r;

    //Chorradas para sacar el numerito que queremos
    st->wheel[st->index]=st->wheel[(unsigned char)(st->index-24)]+ \
                         st->wheel[(unsigned char)(st->index-55)];
    r=(st->wheel[st->index]^(st->wheel[(unsigned char)(st->index-61)]));
    st->index++; //nos movemos en la rueda
    return r;
}
#endif

#endif
