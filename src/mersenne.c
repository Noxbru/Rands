#include <stdlib.h>
#include "rands.h"

#if MT_RAND || RANDS_USE_ALL
    
mt_state mt_default_state;

void mt_srand(unsigned int seed)
{
    unsigned int i;
    srand(seed);
    for(i = 0; i < 624; i++)
        mt_default_state.wheel[i]=rand();
    mt_default_state.index=0;
}

static const uint32_t mt_magic[2] = {0,0x9908b0df};

#ifdef __SSE2__
static const __m128i mt_sse_magic = {0x9908b0df9908b0df,0x9908b0df9908b0df};
static const __m128i mask_00 = {0,0};
#ifndef __SSE4_1__
static const __m128i mask_01 = {0x0000000100000001,0x0000000100000001};
#endif
static const __m128i mask_7f = {0x7fffffff7fffffff,0x7fffffff7fffffff};
static const __m128i mask_80 = {0x8000000080000000,0x8000000080000000};
static const __m128i mask_b  = {0x9d2c56809d2c5680,0x9d2c56809d2c5680};
static const __m128i mask_c  = {0xefc60000efc60000,0xefc60000efc60000};
#endif

void mt_calc()
{
#ifndef __SSE2__
    unsigned int i;
    uint32_t y;

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
    mt_default_state.wheel[623] = mt_default_state.wheel[396] ^ (y>>1) ^ mt_magic[y&1];

    for(i = 0; i < 624; i++)
    {
        y = mt_default_state.wheel[i];
        y^= (y>>11);
        y^= ((y<<7)&0x9d2c5680);
        y^= ((y<<15)&0xefc60000);
        y^= (y>>18);
        mt_default_state.wheel2[i] = y;
    }
#else
    unsigned int i;
    uint32_t z;

    __m128i y;
    __m128i a,b;
    __m128i mask_magic;
    __m128i magic;

    for(i = 0; i < 224; i+=4)
    {
        a = _mm_and_si128(_mm_loadu_si128((__m128i *) &mt_default_state.wheel[i]), mask_80);    // wheel   & 0x80000000
        b = _mm_and_si128(_mm_loadu_si128((__m128i *) &mt_default_state.wheel[i+1]), mask_7f);  // wheel+1 & 0x7fffffff
        y = _mm_or_si128(a,b);                                                                  // y

        a = _mm_loadu_si128((__m128i *) &mt_default_state.wheel[i+397]);                        // wheel+397
        b = _mm_srli_epi32(y,1);                                                                // y >> 1
#ifndef __SSE4_1__
        mask_magic = _mm_and_si128(y,mask_01);                                                  // y & 1
        mask_magic = _mm_cmplt_epi32(mask_00, mask_magic);
        magic = _mm_and_si128(mt_sse_magic, mask_magic);
#else
        mask_magic = _mm_slli_epi32(y,31);
        *((__m128 *) &magic) = _mm_blendv_ps(*((__m128 *) &mask_00),*((__m128 *) &mt_sse_magic),*((__m128 *) &mask_magic));
#endif

        y = _mm_xor_si128(a,b);                                                                 // wheel+397 ^ y >> 1
        y = _mm_xor_si128(y,magic);                                                             //

        _mm_storeu_si128((__m128i *) &mt_default_state.wheel[i],y);
    }
    
    z = (mt_default_state.wheel[224] & 0x80000000) | \
        (mt_default_state.wheel[225] & 0x7fffffff);
    mt_default_state.wheel[224] = mt_default_state.wheel[621] ^ (z>>1) ^ mt_magic[z&1];

    z = (mt_default_state.wheel[225] & 0x80000000) | \
        (mt_default_state.wheel[226] & 0x7fffffff);
    mt_default_state.wheel[225] = mt_default_state.wheel[622] ^ (z>>1) ^ mt_magic[z&1];

    z = (mt_default_state.wheel[226] & 0x80000000) | \
        (mt_default_state.wheel[227] & 0x7fffffff);
    mt_default_state.wheel[226] = mt_default_state.wheel[623] ^ (z>>1) ^ mt_magic[z&1];

    for(i = 227; i < 623; i+=4)
    {
        a = _mm_and_si128(_mm_loadu_si128((__m128i *) &mt_default_state.wheel[i]), mask_80);    // wheel   & 0x80000000
        b = _mm_and_si128(_mm_loadu_si128((__m128i *) &mt_default_state.wheel[i+1]), mask_7f);  // wheel+1 & 0x7fffffff
        y = _mm_or_si128(a,b);                                                                  // y

        a = _mm_loadu_si128((__m128i *) &mt_default_state.wheel[i-227]);                        // wheel+397
        b = _mm_srli_epi32(y,1);                                                                // y >> 1
#ifndef __SSE4_1__
        mask_magic = _mm_and_si128(y,mask_01);                                                  // y & 1
        mask_magic = _mm_cmplt_epi32(mask_00,mask_magic);
        magic = _mm_and_si128(mt_sse_magic, mask_magic);
#else
        mask_magic = _mm_slli_epi32(y,31);
        *((__m128 *) &magic) = _mm_blendv_ps(*((__m128 *) &mask_00),*((__m128 *) &mt_sse_magic),*((__m128 *) &mask_magic));
#endif

        y = _mm_xor_si128(a,b);                                                                 // wheel+397 ^ y >> 1
        y = _mm_xor_si128(y,magic);                                                             //

        _mm_storeu_si128((__m128i *) &mt_default_state.wheel[i],y);
    }

    z = (mt_default_state.wheel[623] & 0x80000000) | \
        (mt_default_state.wheel[0] & 0x7fffffff);
    mt_default_state.wheel[623] = mt_default_state.wheel[396] ^ (z>>1) ^ mt_magic[z&1];

    for(i = 0; i < 624; i+=4)
    {
        y = _mm_loadu_si128((__m128i *) &mt_default_state.wheel[i]);

        a = _mm_srli_epi32(y,11);
        y = _mm_xor_si128(y,a);         // y ^= y>>11

        a = _mm_slli_epi32(y,7);
        b = _mm_and_si128(a,mask_b);
        y = _mm_xor_si128(y,b);         // y ^= (y<<7) & 0x9d2c5680

        a = _mm_slli_epi32(y,15);
        b = _mm_and_si128(a,mask_c);
        y = _mm_xor_si128(y,b);         // y ^= (y<<15) & 0xefc60000

        a = _mm_srli_epi32(y,18);
        y = _mm_xor_si128(y,a);         // y ^= y>>18

        _mm_storeu_si128((__m128i *) &mt_default_state.wheel2[i],y);
    }
#endif
    mt_default_state.index = 0;
}

inline uint32_t mt_rand()
{
    uint32_t r;
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

void mt_srand_st(mt_state *st, unsigned int seed)
{
    unsigned int i;
    srand(seed);
    for(i = 0; i < 624; i++)
        st->wheel[i]=rand();
    st->index=0;
}

void mt_calc_st(mt_state *st)
{
#ifndef __SSE2__
    unsigned int i;
    uint32_t y;

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
    st->wheel[623] = st->wheel[396] ^ (y>>1) ^ mt_magic[y&1];

    for(i = 0; i < 624; i++)
    {
        y = st->wheel[i];
        y^= (y>>11);
        y^= ((y<<7)&0x9d2c5680);
        y^= ((y<<15)&0xefc60000);
        y^= (y>>18);
        st->wheel2[i] = y;
    }
#else
    unsigned int i;
    uint32_t z;

    __m128i y;
    __m128i a,b;
    __m128i mask_magic;
    __m128i magic;

    for(i = 0; i < 224; i+=4)
    {
        a = _mm_and_si128(_mm_loadu_si128((__m128i *) &st->wheel[i]), mask_80);
        b = _mm_and_si128(_mm_loadu_si128((__m128i *) &st->wheel[i+1]), mask_7f);
        y = _mm_or_si128(a,b);

        a = _mm_loadu_si128((__m128i *) &st->wheel[i+397]);
        b = _mm_srli_epi32(y,1);
#ifndef __SSE4_1__
        mask_magic = _mm_and_si128(y,mask_01);
        mask_magic = _mm_cmplt_epi32(mask_00, mask_magic);
        magic = _mm_and_si128(mt_sse_magic, mask_magic);
#else
        mask_magic = _mm_slli_epi32(y,31);
        *((__m128 *) &magic) = _mm_blendv_ps(*((__m128 *) &mask_00),*((__m128 *) &mt_sse_magic),*((__m128 *) &mask_magic));
#endif

        y = _mm_xor_si128(a,b);
        y = _mm_xor_si128(y,magic);

        _mm_storeu_si128((__m128i *) &st->wheel[i],y);
    }
    
    z = (st->wheel[224] & 0x80000000) | \
        (st->wheel[225] & 0x7fffffff);
    st->wheel[224] = st->wheel[621] ^ (z>>1) ^ mt_magic[z&1];

    z = (st->wheel[225] & 0x80000000) | \
        (st->wheel[226] & 0x7fffffff);
    st->wheel[225] = st->wheel[622] ^ (z>>1) ^ mt_magic[z&1];

    z = (st->wheel[226] & 0x80000000) | \
        (st->wheel[227] & 0x7fffffff);
    st->wheel[226] = st->wheel[623] ^ (z>>1) ^ mt_magic[z&1];

    for(i = 227; i < 623; i+=4)
    {
        a = _mm_and_si128(_mm_loadu_si128((__m128i *) &st->wheel[i]), mask_80);
        b = _mm_and_si128(_mm_loadu_si128((__m128i *) &st->wheel[i+1]), mask_7f);
        y = _mm_or_si128(a,b);

        a = _mm_loadu_si128((__m128i *) &st->wheel[i-227]);
        b = _mm_srli_epi32(y,1);
#ifndef __SSE4_1__
        mask_magic = _mm_and_si128(y,mask_01);
        mask_magic = _mm_cmplt_epi32(mask_00,mask_magic);
        magic = _mm_and_si128(mt_sse_magic, mask_magic);
#else
        mask_magic = _mm_slli_epi32(y,31);
        *((__m128 *) &magic) = _mm_blendv_ps(*((__m128 *) &mask_00),*((__m128 *) &mt_sse_magic),*((__m128 *) &mask_magic));
#endif

        y = _mm_xor_si128(a,b);
        y = _mm_xor_si128(y,magic);

        _mm_storeu_si128((__m128i *) &st->wheel[i],y);
    }

    z = (st->wheel[623] & 0x80000000) | \
        (st->wheel[0] & 0x7fffffff);
    st->wheel[623] = st->wheel[396] ^ (z>>1) ^ mt_magic[z&1];

    for(i = 0; i < 624; i+=4)
    {
        y = _mm_loadu_si128((__m128i *) &st->wheel[i]);

        a = _mm_srli_epi32(y,11);
        y = _mm_xor_si128(y,a);

        a = _mm_slli_epi32(y,7);
        b = _mm_and_si128(a,mask_b);
        y = _mm_xor_si128(y,b);

        a = _mm_slli_epi32(y,15);
        b = _mm_and_si128(a,mask_c);
        y = _mm_xor_si128(y,b);

        a = _mm_srli_epi32(y,18);
        y = _mm_xor_si128(y,a);

        _mm_storeu_si128((__m128i *) &st->wheel2[i],y);
    }
#endif
    st->index = 0;
}

inline uint32_t mt_rand_st(mt_state *st)
{
    uint32_t r;
    if(!st->index)
        mt_calc_st(st);
    r = st->wheel2[st->index];
    st->index = (st->index + 1)%624;
    return r;
}
#endif

#endif
