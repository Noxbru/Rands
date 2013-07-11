#include <stdlib.h>
#include "rands.h"

#if MT_RAND || RANDS_USE_ALL
    
mt_state mt_default_state;
static unsigned int mt_magic[2] = {0,0x9908b0df};

void mt_srand(unsigned long int seed)
{
    unsigned int i;
    srand(seed);
    for(i = 0; i < 624; i++)
        mt_default_state.wheel[i]=rand();
    mt_default_state.index=0;
}

void mt_calc()
{
    unsigned int i,y;

    for(i = 0; i < 227; i++)
    {
        y = (mt_default_state.wheel[i] & 0x80000000) | \
            (mt_default_state.wheel[i+1] & 0x7fffffff);
        mt_default_state.wheel[i] = mt_default_state.wheel[i+397] ^ (y>>1) ^ mt_magic[y&1];
    }
    
    for(; i < 623; i++)
    {
        y = (mt_default_state.wheel[i] & 0x80000000) | \
            (mt_default_state.wheel[i+1] & 0x7fffffff);
        mt_default_state.wheel[i] = mt_default_state.wheel[i-227] ^ (y>>1) ^ mt_magic[y&1];
    }

    y = (mt_default_state.wheel[623] & 0x80000000) | \
        (mt_default_state.wheel[0] & 0x7fffffff);
    mt_default_state.wheel[623] = mt_default_state.wheel[296] ^ (y>>1) ^ mt_magic[y&1];

    for(i = 0; i < 624; i++)
    {
        y = mt_default_state.wheel[i];
        y^= (y>>11);
        y^= ((y<<7)&0x9d2c5680);
        y^= ((y<<15)&0xefc60000);
        y^= (y>>18);
        mt_default_state.wheel2[i] = y;
    }

    mt_default_state.index = 0;
}

unsigned int mt_rand()
{
    unsigned int r;
    if(!mt_default_state.index)
        mt_calc();
    r = mt_default_state.wheel2[mt_default_state.index];
    mt_default_state.index = (mt_default_state.index + 1)%624;
    return r;
}

#if RANDS_USE_STATES
inline void mt_init_st(mt_state **st)
{
    (*st)=malloc(sizeof(mt_state));
}

inline void mt_clear_st(mt_state *st)
{
    free(st);
}

void mt_srand_st(mt_state *st, unsigned long int seed)
{
    unsigned int i;
    srand(seed);
    for(i = 0; i < 624; i++)
        st->wheel[i]=rand();
    st->index=0;
}

void mt_calc_st(mt_state *st)
{
    unsigned int i,y;

    for(i = 0; i < 227; i++)
    {
        y = (st->wheel[i] & 0x80000000) | \
            (st->wheel[i+1] & 0x7fffffff);
        st->wheel[i] = st->wheel[i+397] ^ (y>>1) ^ mt_magic[y&1];
    }

    for(; i < 623; i++)
    {
        y = (st->wheel[i] & 0x80000000) | \
            (st->wheel[i+1] & 0x7fffffff);
        st->wheel[i] = st->wheel[i-227] ^ (y>>1) ^ mt_magic[y&1];
    }

    y = (st->wheel[623] & 0x80000000) | \
        (st->wheel[0] & 0x7fffffff);
    st->wheel[623] = st->wheel[296] ^ (y>>1) ^ mt_magic[y&1];

    for(i = 0; i < 624; i++)
    {
        y = st->wheel[i];
        y^= (y>>11);
        y^= ((y<<7)&0x9d2c5680);
        y^= ((y<<15)&0xefc60000);
        y^= (y>>18);
        st->wheel2[i] = y;
    }
    st->index = 0;
}

unsigned int mt_rand_st(mt_state *st)
{
    unsigned int r;
    if(!st->index)
        mt_calc_st(st);
    r = st->wheel2[st->index];
    st->index = (st->index + 1)%624;
    return r;
}
#endif

#endif
