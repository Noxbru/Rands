/* 
 * Default values for the first states of the wheel by
 * Marsaglia:
 *  - 123456789
 *  - 362436069
 *  - 521288629
 *  - 88675123
 */

#include <stdlib.h>
#include "rands.h"

#if XOR_RAND || RANDS_USE_ALL

xor_state xor_default_state;

void xor_srand(unsigned long int seed)
{
    srand(seed);
    xor_default_state.wheel[0]=rand();
    xor_default_state.wheel[1]=rand();
    xor_default_state.wheel[2]=rand();
    xor_default_state.wheel[3]=rand();
}

unsigned int xor_rand()
{
    unsigned int t=xor_default_state.wheel[0]^(xor_default_state.wheel[0]<<11);
    unsigned int a=xor_default_state.wheel[3]^(xor_default_state.wheel[3]>>19);
//if __SSE2__
    /*
     *__m128i b = _mm_load_si128((__m128i *) xor_default_state.wheel);
     *b = _mm_srli_si128(b,4);
     *_mm_store_si128((__m128i *) xor_default_state.wheel,b);
     */
//#else
    xor_default_state.wheel[0]=xor_default_state.wheel[1];
    xor_default_state.wheel[1]=xor_default_state.wheel[2];
    xor_default_state.wheel[2]=xor_default_state.wheel[3];
//#endif
    xor_default_state.wheel[3]=a ^ (t^(t>>8));
    return xor_default_state.wheel[3];
}

#if RANDS_USE_STATES
inline void xor_init_st(xor_state **st)
{
    (*st)=malloc(sizeof(xor_state)); 
}

inline void xor_clear_st(xor_state *st)
{
    free(st);
}

void xor_srand_st(xor_state *st, unsigned long int seed)
{
    srand(seed);
    st->wheel[0]=rand();
    st->wheel[1]=rand();
    st->wheel[2]=rand();
    st->wheel[3]=rand();
}

unsigned int xor_rand_st(xor_state *st)
{
    unsigned int t=st->wheel[0]^(st->wheel[0]<<11);
    unsigned int a=st->wheel[3]^(st->wheel[3]>>19);
    st->wheel[0]=st->wheel[1];
    st->wheel[1]=st->wheel[2];
    st->wheel[2]=st->wheel[3];
    st->wheel[3]=a ^ (t^(t>>8));
    return st->wheel[3];
}
#endif

#endif
