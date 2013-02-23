/* The code for generating random numbers is taken
 * from the paper 'Random Number Generation' by
 * Chris Lomont. It is released in the public
 * domain, but he'd appreciate a reference, so
 * here it is (^_^)                                 */
#include <stdlib.h>
#include "rands.h"

#if WELL_RAND || RANDS_USE_ALL

well_state well_default_state;

void well_srand(unsigned long seed)
{
    unsigned char i;

    srand(seed);
    for(i = 0; i < 16; i++)
        well_default_state.wheel[i]=rand();

    well_default_state.index=0;
}

unsigned int well_rand()
{
    unsigned int a,b,c,d;
    a=well_default_state.wheel[well_default_state.index];
    c=well_default_state.wheel[(well_default_state.index+13)&15];
    b=a^c^(a<<16)^(c<<15);
    c=well_default_state.wheel[(well_default_state.index+9)&15];
    c^=(c>>11);

    a=well_default_state.wheel[well_default_state.index]=b^c;
    d=a^((a<<5)&0xDA442D24UL);
    well_default_state.index=(well_default_state.index+15)&15;
    a=well_default_state.wheel[well_default_state.index];
    well_default_state.wheel[well_default_state.index]=a^b^d^(a<<2)^(b<<18)^(c<<28);
    return well_default_state.wheel[well_default_state.index];
}

#if RANDS_USE_STATES
void inline well_init_st(well_state **st)
{
    (*st)=malloc(sizeof(well_state)); 
}

void inline well_clear_st(well_state *st)
{
    free(st);
}

void well_srand_st(well_state *st, unsigned long seed)
{
    unsigned char i;

    srand(seed);
    for(i = 0; i < 16; i++)
        st->wheel[i]=rand();

    st->index=0;
}

unsigned int well_rand_st(well_state *st)
{
    unsigned int a,b,c,d;
    a=st->wheel[st->index];
    c=st->wheel[(st->index+13)&15];
    b=a^c^(a<<16)^(c<<15);
    c=st->wheel[(st->index+9)&15];
    c^=(c>>11);

    a=st->wheel[st->index]=b^c;
    d=a^((a<<5)&0xDA442D24UL);
    st->index=(st->index+15)&15;
    a=st->wheel[st->index];
    st->wheel[st->index]=a^b^d^(a<<2)^(b<<18)^(c<<28);
    return st->wheel[st->index];
}
#endif

#endif
