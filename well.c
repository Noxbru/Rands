/* This code has been inspired by the one at the
 * paper 'Random Number Generation' by Chris Lomont
 * with some changes I have done after I have
 * discovered how the algorithm works.
 * 
 * Also, his code is released in the public domain,
 * but he'd appreciate a reference, so here it is
 * (^_^)                                            */

/* Here is the explanation of the algorithm as I have
 * managed to understand. This corresponds to
 * WELL512, but it may be used in combination to
 * the paper to fully understand an example and
 * implement the others.
 * 
 * All the operations are performed modulo 16, so
 * for example i+13 has to be understood as
 * (i+13)%16 or as in the code (i+13)&15
 * 
 * We will use four variables, one for each of the
 * numbers needed for the final calculation of the
 * state.
 * 
 * ----------------------------------------------------------------
 * a = state[ind]
 * b = state[ind+13]
 * c = state[ind+9]
 * 
 * b = a^(a<<16)^b^(b<<15)      (z1)
 * c = c^(c>>11)                (z2)
 * d = b^c                      (z3)
 * 
 * state[ind] = d
 * ind = ind - 1
 * a = state[ind]               (z0)
 * 
 * state[ind] = a^(a^<<2)^b^(b<<18)^(c<<28)^d^((d<<5)&0xda442d24UL)
 * 
 * return state[ind]
 * ----------------------------------------------------------------
 * 
 * The original code from Francois Panneton, Pierre
 * L'Ecuyer and Makoto Matsumoto mainly does the
 * same but performs the ind-- as the last step
 * doing some more computations for getting z0
 * and the new state. We also return an uint32_t
 * instead of a double, so it's the user who can
 * choose what to do with the final number
 *
 * The original code can be taken from here:
 * http://www.iro.umontreal.ca/~panneton/WELLRNG.html
 */


#include "rands.h"

#if WELL_RAND || RANDS_USE_ALL

well_state well_default_state;

void well_srand(unsigned int seed)
{
    unsigned char i;

    srand(seed);
    for(i = 0; i < 16; i++)
        well_default_state.wheel[i]=rand();

    well_default_state.index=0;
}

uint32_t well_rand()
{
    uint32_t a,b,c,d;
    a=well_default_state.wheel[well_default_state.index];
    b=well_default_state.wheel[(well_default_state.index+13)&15];
    c=well_default_state.wheel[(well_default_state.index+9)&15];

    b=a^(a<<16)^b^(b<<15);
    c^=(c>>11);

    well_default_state.wheel[well_default_state.index]=d=b^c;
    well_default_state.index=(well_default_state.index+15)&15;
    a=well_default_state.wheel[well_default_state.index];

    d=d^((d<<5)&0xDA442D24UL);
    well_default_state.wheel[well_default_state.index]=a^(a<<2)^b^(b<<18)^(c<<28)^d;
    return well_default_state.wheel[well_default_state.index];
}

#if RANDS_USE_STATES
inline void well_init_st(well_state **st)
{
    (*st)=malloc(sizeof(well_state)); 
}

inline void well_clear_st(well_state *st)
{
    free(st);
}

void well_srand_st(well_state *st, unsigned int seed)
{
    unsigned char i;

    srand(seed);
    for(i = 0; i < 16; i++)
        st->wheel[i]=rand();

    st->index=0;
}

uint32_t well_rand_st(well_state *st)
{
    uint32_t a,b,c,d;
    a=st->wheel[st->index];
    b=st->wheel[(st->index+13)&15];
    c=st->wheel[(st->index+9)&15];

    b=a^(a<<16)^b^(b<<15);
    c^=(c>>11);

    st->wheel[st->index]=d=b^c;
    st->index=(st->index+15)&15;
    a=st->wheel[st->index];

    d=d^((d<<5)&0xDA442D24UL);
    st->wheel[st->index]=a^(a<<2)^b^(b<<18)^(c<<28)^d;
    return st->wheel[st->index];
}
#endif

#endif
